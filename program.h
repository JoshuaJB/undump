#ifndef __PROGRAM_H__
#define __PROGRAM_H__

#include <sys/types.h>
#include "elfcommon.h"

struct program {
    Elf_Ehdr *header;
    char *prog;
    int fd;
    off_t size;
};


struct program *prog_read_elf(const char *filename);

Elf_Phdr *prog_get_program_headers(struct program *p);
Elf_Shdr *prog_get_sections(struct program *p);
char *prog_get_section_name(struct program *p, Elf_Shdr *s);
void dump_program_data(struct program *p);

#endif

