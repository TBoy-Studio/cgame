#include <tengine.h>
#include <assert.h>

int main(int argc, char **argv)
{
    cgame_file_init(argv[0]);

    FILE *file = cgame_file_open("../../src/file.c", "rb");
    fclose(file);
}