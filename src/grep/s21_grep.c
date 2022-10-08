#include <err.h>
#include <error.h>
#include <regex.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define BUFF 100
#define MAX 1024

typedef struct {
    int i;
    int v;
    int c;
    int l;
    int n;
    int h;
    int s;
    int o;
    int no_flags;
} out_flags;

int file_parser(char pattern[BUFF][MAX], char *file_name, int *p_qty, int *pat_pos);
char *s21_fgets(FILE *file, char *pattern);
void struct_init(out_flags *flags);
int flag_parser(out_flags *flags, int *p_qty, int argc, char **argv, char pattern[BUFF][MAX],
                char files[BUFF][MAX], int *f_qty, int *ef_exist);
int check_struct(out_flags *flags);
void do_flags(char a, out_flags *flags);
int pars_prep(int argc, char **argv, int *ef_exist);
int row_count(FILE *file);
int processing(out_flags *flags, char pattern[BUFF][MAX], int *p_qty, char files[BUFF][MAX], int *f_qty);
int i_param(out_flags *flags);
int o_param(out_flags *flags);
void *o_param_pnt(out_flags *flags, regmatch_t *pmatch);
int output(out_flags *flags, char *temp, int r, char *file_name, int f_qty, int count);
int processing_row(char *files, int *f_qty, int r, out_flags *flags, char *str, char pattern[BUFF][MAX],
                   int p_qty, int *q_match, int r_count, int *q_non_match);

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("EMPTY\n");
        return 0;
    }
    char pattern[BUFF][MAX];  // Массив, для паттернов из аргументов
    char files[BUFF][MAX];  // Массив, в который будут записываться названия файлов
    int p_qty = 0, f_qty = 0, ef_exist = 0;
    int argc_copy = argc;
    char **argv_copy;
    argv_copy = argv;
    out_flags flags;
    struct_init(&flags);
    pars_prep(argc_copy, argv_copy, &ef_exist);
    flag_parser(&flags, &p_qty, argc_copy, argv_copy, pattern, files, &f_qty, &ef_exist);
    processing(&flags, pattern, &p_qty, files, &f_qty);
    return EXIT_SUCCESS;
}

// Готовая функция по полному выводу строки без дополнительных флагов
int processing(out_flags *flags, char pattern[BUFF][MAX], int *p_qty, char files[BUFF][MAX], int *f_qty) {
    if (check_struct(flags)) {
        ;
    }
    int f;
    for (f = 0; f < *f_qty; f++) {
        int q_match = 0;
        int q_non_match = 0;
        FILE *file = NULL;
        file = fopen(files[f], "r");
        if (file == NULL && flags->s == 0) {
            fprintf(stderr, "grep: %s: %s\n", files[f], strerror(2));
            continue;
        } else if (file == NULL && flags->s != 0) {
            continue;
        }
        int r_count = row_count(file);
        fseek(file, 0, SEEK_SET);
        for (int r = 0; r < r_count - 1; r++) {
            char str[MAX];
            memset(str, '\0', MAX);
            s21_fgets(file, str);
            processing_row(files[f], f_qty, r, flags, str, pattern, *p_qty, &q_match, r_count, &q_non_match);
        }
        fclose(file);
        if (flags->c == 1 && flags->l == 0) {
            if (*f_qty > 1) {
                if (flags->v == 1) {
                    if (flags->h == 0) {
                        printf("%s:%d\n", files[f], r_count - 1 - q_match);
                    } else {
                        printf("%d\n", r_count - 1 - q_match);
                    }
                } else {
                    if (flags->h == 0) {
                        printf("%s:%d\n", files[f], q_match);
                    } else {
                        printf("%d\n", q_match);
                    }
                }
            } else {
                if (flags->v == 1) {
                    printf("%d\n", r_count - 1 - q_match);
                } else {
                    printf("%d\n", q_match);
                }
            }
        } else if (flags->l == 1) {
            if (flags->v == 1 && q_non_match > 0) {
                printf("%s\n", files[f]);
            } else if (flags->v == 0 && q_match > 0) {
                printf("%s\n", files[f]);
            }
        }
    }
    return EXIT_SUCCESS;
}

int processing_row(char *files, int *f_qty, int r, out_flags *flags, char *str, char pattern[BUFF][MAX],
                   int p_qty, int *q_match, int r_count, int *q_non_match) {
    regex_t regex;
    regmatch_t pmatch;
    char temp[MAX];
    char *temp2 = str;
    int q_match_in_row = 0, n_match_in_row = 0;
    if (flags->o == 0 || (flags->o == 1 && flags->l == 1)) {
        for (int p = 0; p < p_qty; p++) {
            if (regcomp(&regex, pattern[p], i_param(flags)) != 0) {
                regfree(&regex);
                continue;
            }
            if (regexec(&regex, temp2, o_param(flags), o_param_pnt(flags, &pmatch), 0) == 0) {
                q_match_in_row++;
                if (q_match_in_row == 1 && flags->c == 0 && flags->l == 0 && flags->v == 0) {
                    strcpy(temp, temp2);
                    output(flags, temp, r, files, *f_qty, r_count);
                }
                regfree(&regex);
            } else {
                n_match_in_row++;
                *q_non_match += 1;
            }
            regfree(&regex);
        }
        if (flags->v == 1 && q_match_in_row == 0) {
            if (flags->c == 0 && flags->l == 0) {
                strcpy(temp, temp2);
                output(flags, temp, r, files, *f_qty, r_count);
            }
        }
        regfree(&regex);
    } else {
        while (*temp2 != '\0') {
            memset(temp, '\0', MAX);
            long int min_offset = -1;
            long int max_offset = 0;
            int offset = 0;
            for (int p = 0; p < p_qty; p++) {
                if (regcomp(&regex, pattern[p], i_param(flags)) != 0) {
                    regfree(&regex);
                    continue;
                }
                if (regexec(&regex, temp2, o_param(flags), o_param_pnt(flags, &pmatch), 0) == 0) {
                    q_match_in_row++;
                    // Writing first match
                    if (min_offset == -1) {
                        min_offset = pmatch.rm_so;
                        max_offset = pmatch.rm_eo;
                        regfree(&regex);
                        continue;
                    }
                    // If rm_so isn't first match skip iteration
                    if (pmatch.rm_so > min_offset) {
                        regfree(&regex);
                        continue;
                    } else {
                        min_offset = pmatch.rm_so;
                        max_offset = pmatch.rm_eo;
                        regfree(&regex);
                        continue;
                    }
                    if (pmatch.rm_so == min_offset && pmatch.rm_eo > max_offset) {
                        min_offset = pmatch.rm_so;
                        max_offset = pmatch.rm_eo;
                        regfree(&regex);
                        continue;
                    }
                } else {
                    regfree(&regex);
                    continue;
                }
                regfree(&regex);
            }
            if (min_offset == -1) {
                regfree(&regex);
                break;
            }
            offset = max_offset - min_offset;
            memmove(temp, temp2 + min_offset, offset);
            if (flags->c == 0 && flags->l == 0) output(flags, temp, r, files, *f_qty, r_count);
            temp2 += max_offset;
        }
    }
    if (q_match_in_row > 0) *q_match += 1;
    return EXIT_SUCCESS;
}

int output(out_flags *flags, char *temp, int r, char *file_name, int f_qty, int r_count) {
    if (flags->n == 1) {
        if (f_qty > 1 && !flags->h) {
            if (r < r_count) {
                printf("%s:%d:%s", file_name, r + 1, temp);
                putchar('\n');
            } else {
                printf("%s:%d:%s", file_name, r + 1, temp);
            }
        } else {
            if (r < r_count) {
                printf("%d:%s", r + 1, temp);
                putchar('\n');
            } else {
                printf("%d:%s", r + 1, temp);
            }
        }
    } else {
        if (f_qty > 1 && !flags->h) {
            if (r < r_count - 1) {
                printf("%s:%s", file_name, temp);
                putchar('\n');
            } else {
                printf("%s:%s", file_name, temp);
            }
        } else {
            if (r < r_count - 1) {
                printf("%s", temp);
                putchar('\n');
            } else {
                printf("%s", temp);
            }
        }
    }
    return EXIT_SUCCESS;
}

void *o_param_pnt(out_flags *flags, regmatch_t *pmatch) { return (flags->o == 1) ? pmatch : NULL; }

int i_param(out_flags *flags) { return (flags->i == 1) ? 2 : 1; }

int o_param(out_flags *flags) { return (flags->o == 1) ? 1 : 0; }

int pars_prep(int argc, char **argv, int *ef_exist) {
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-' && argv[i][1] == 'f') {
            *ef_exist += 1;
        }
        if (argv[i][0] == '-' && argv[i][1] == 'e') {
            *ef_exist += 1;
        }
    }
    return 0;
}

int flag_parser(out_flags *flags, int *p_qty, int argc, char **argv, char pattern[BUFF][MAX],
                char files[BUFF][MAX], int *f_qty, int *ef_exist) {
    char *grep = "-ivclnhso";
    int pat_pos = 0;
    int argv_flag = 0;  // Flag to check pattern arguments
    int file_pos = 0;
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-' && argv[i][1] != '-' && argv[i][1] != 'e' && argv[i][1] != 'f') {
            for (size_t j = 1; j < strlen(argv[i]); j++) {
                if ((strchr(grep, argv[i][j])) != NULL) {
                    do_flags(argv[i][j], flags);
                } else {
                    printf("NO FLAGS\n");
                    break;
                }
            }
        } else if (argv[i][0] == '-' && argv[i][1] == 'e') {
            i++;
            strcpy(pattern[pat_pos], argv[i]);
            pat_pos++;
            *p_qty += 1;
            // argv_flag = 1; Think about this
        } else if (argv[i][0] == '-' && argv[i][1] == 'f') {
            i++;
            file_parser(pattern, argv[i], p_qty, &pat_pos);
            argv_flag = 1;
        } else if (check_struct(flags) | !check_struct(flags) && argv_flag == 0 && *ef_exist == 0) {
            strcpy(pattern[pat_pos], argv[i]);
            pat_pos++;
            *p_qty += 1;
            argv_flag = 1;
        } else if (check_struct(flags) | !check_struct(flags) && argv_flag == 0 && *ef_exist > 0) {
            strcpy(files[file_pos], argv[i]);
            file_pos++;
            *f_qty += 1;
        } else if (argv_flag == 1) {
            strcpy(files[file_pos], argv[i]);
            file_pos++;
            *f_qty += 1;
        }
    }
    if (flags->o == 1 && flags->v == 1 && flags->c == 0 && flags->l == 0) exit(0);
    return 0;
}

void do_flags(char a, out_flags *flags) {
    if (a == 'i') {
        flags->i = 1;
    } else if (a == 'v') {
        flags->v = 1;
    } else if (a == 'c') {
        flags->c = 1;
    } else if (a == 'l') {
        flags->l = 1;
    } else if (a == 'n') {
        flags->n = 1;
    } else if (a == 'h') {
        flags->h = 1;
    } else if (a == 's') {
        flags->s = 1;
    } else if (a == 'o') {
        flags->o = 1;
    }
}

int check_struct(out_flags *flags) {
    return (flags->i == 0 && flags->v == 0 && flags->c == 0 && flags->l == 0 && flags->n == 0 &&
            flags->h == 0 && flags->s == 0 && flags->o == 0)
               ? 1
               : 0;
}

void struct_init(out_flags *flags) {
    flags->i = 0;
    flags->v = 0;
    flags->c = 0;
    flags->l = 0;
    flags->n = 0;
    flags->h = 0;
    flags->s = 0;
    flags->o = 0;
}

int file_parser(char pattern[BUFF][MAX], char *file_name, int *p_qty, int *pat_pos) {
    FILE *file = NULL;
    file = fopen(file_name, "r");
    if (file == NULL) {
        fprintf(stderr, "grep: %s: %s\n", file_name, strerror(2));
        exit(2);
    }
    int r_count = row_count(file);
    fseek(file, 0, SEEK_SET);
    for (int i = 0; i < r_count - 1; i++) {
        s21_fgets(file, pattern[*pat_pos]);
        *p_qty += 1;
        if (pattern[*pat_pos][0] == '\0') {
            pattern[*pat_pos][0] = '\0';
        }
        *pat_pos += 1;
    }
    fclose(file);
    return EXIT_SUCCESS;
}

char *s21_fgets(FILE *file, char *pattern) {
    char c;
    int i = 0;
    while ((c = fgetc(file)) != '\n' && c != EOF) {
        pattern[i] = c;
        i++;
    }
    pattern[i] = '\0';
    return pattern;
}

int row_count(FILE *file) {
    int count = 0;
    char c;
    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') {
            count++;
        }
    }
    if (c == EOF) count++;
    return count;
}
