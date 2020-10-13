#ifndef __ELF_COMMON_H__
#define __ELF_COMMON_H__


#include <elf.h>

#if defined(__x86_64__)
#define Elf_Phdr Elf64_Phdr
#define Elf_Ehdr Elf64_Ehdr
#define Elf_Shdr Elf64_Shdr
#define Elf_Nhdr Elf64_Nhdr
#else
#define Elf_Phdr Elf32_Phdr
#define Elf_Ehdr Elf_Ehdr
#define Elf_Shdr Elf32_Shdr
#define Elf_Nhdr Elf32_Nhdr
#endif


typedef struct {
    Elf_Phdr phdr;
    char *segment;
} undump_segment;

typedef struct {
    Elf_Ehdr ehdr;
    undump_segment *segments;
} undumped_program;

Elf_Shdr *elf_get_sections(char *c);
char *elf_get_section_strings(char *c);
char *elf_get_section_name(char *c, Elf_Shdr *s);
Elf_Phdr *elf_get_program_headers(char *c);

/* Methods to manipulate the undumped_program struct */

undump_segment *elf_add_segment(undumped_program *und, char *segment, Elf_Phdr *phdr);
undumped_program *elf_new_undumped_program();
uint32_t elf_get_nextvaddr(undumped_program *p);

#define elf_get_elf_header(c) ((Elf_Ehdr*)c)

#endif
