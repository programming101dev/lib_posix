#include <stdio.h>
#include <stdlib.h>
#include <iconv.h>
#include <string.h>
#include <errno.h>

int main() {
    iconv_t cd = iconv_open("ISO-8859-1", "UTF-8");
    if (cd == (iconv_t)-1) {
        perror("iconv_open failed");
        return 1;
    }

    char input[] = "Hello, 世界";  // UTF-8 input (contains non-ASCII characters)
    size_t in_bytes_left = strlen(input);
    size_t out_bytes_left = in_bytes_left * 2;  // Make sure output buffer is large enough

    char *in_ptr = input;
    char output[out_bytes_left];
    char *out_ptr = output;
    memset(output, 0, out_bytes_left);

    if (iconv(cd, &in_ptr, &in_bytes_left, &out_ptr, &out_bytes_left) == (size_t)-1) {
        perror("iconv conversion failed");
        iconv_close(cd);
        return 1;
    }

    printf("Converted text: %s\n", output);

    iconv_close(cd);
    return 0;
}

