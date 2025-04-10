
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 8192

//////////////////////宣告函數

//////////////////////讀.meta

void read_meta_file(const char *meta_filename, int *chunk_number, int *chunk_size, char *prefix)
{
    // fopen($path      , $mode)
    FILE *meta = fopen(meta_filename, "r");

    if (!meta)
    {
        perror("Failed to open meta file");
        exit(1);
    }

    fscanf(meta, "%d\n%d\n%s\n", chunk_number, chunk_size, prefix);
    fclose(meta);
}

//////////////////////heal fun

void heal_file(const char *prefix, int chunk_number, int chunk_size, const char *output_filename)
{

    FILE *out = fopen(output_filename, "w");

    if (!out)
    {
        printf("Failed to create output file");
        exit(1);
    }

    for (int i = 0; i < chunk_number; i++)
    {
        char chunk_filename[MAX_NAME];
        sprintf(chunk_filename, "%s.%032d", prefix, i);

        FILE *chunk = fopen(chunk_filename, "r");
        if (!chunk)
        {
            fprintf(stderr, "Error: Missing chunk %s\n", chunk_filename);
            fclose(out);
            exit(1);
        }

        // 檢查 chunk 大小（最後一個 chunk 除外）

        // int fseek(FILE *stream, long offset, int whence);
        // stream：開啟的檔案（f = fopen(...) 得到的）
        // offset：你想移動多少位元組
        // whence：你要從哪個位置開始移動，有三種選項：

        // long ftell(FILE *stream); 檔案開頭的位元組位置

        fseek(chunk, 0, SEEK_END);
        long chunk_actual_size = ftell(chunk);
        rewind(chunk);
        if (i < chunk_number - 1 && chunk_actual_size != chunk_size)
        {
            fprintf(stderr, "Error: Chunk size mismatch for %s (expected %d, got %ld)\n",
                    chunk_filename, chunk_size, chunk_actual_size);
            fclose(chunk);
            fclose(out);
            exit(1);
        }

        // 讀取並寫入
        char *buffer = (char *)malloc(chunk_size);
        fread(buffer, 1, chunk_actual_size, chunk);
        fwrite(buffer, 1, chunk_actual_size, out);
        fclose(chunk);
        free(buffer);

        printf("Putting %s\n", chunk_filename);
    }

    fclose(out);
    printf("Done! Output file: %s\n", output_filename);
}

//////////////////////執行

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s <meta_prefix> <output_filename>\n", argv[0]);
    }

    char meta_filename[MAX_NAME];

    snprintf(meta_filename, MAX_NAME, "%s.meta", argv[1]);

    int chunk_number, chunk_size;
    char prefix[MAX_NAME];

    read_meta_file(meta_filename, &chunk_number, &chunk_size, prefix);

    heal_file(prefix, chunk_number, chunk_size, argv[2]);

    return 0;
}
