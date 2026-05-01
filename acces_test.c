#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

void check_access(const char *filename) {
    printf("Перевірка для файлу %s:\n", filename);
    if (access(filename, R_OK) == 0) printf("- Читання: ДОЗВОЛЕНО\n");
    else printf("- Читання: ЗАБОРОНЕНО\n");

    if (access(filename, W_OK) == 0) printf("- Запис: ДОЗВОЛЕНО\n");
    else printf("- Запис: ЗАБОРОНЕНО\n");
}

int main() {
    char filename[] = "test_file.txt";

    int fd = creat(filename, 0644);
    if (fd == -1) {
        perror("Помилка створення файлу");
        return 1;
    }
    close(fd);
    printf("Файл створено від імені звичайного користувача.\n");
    check_access(filename);

    printf("\nЗміна власника на root та прав доступу на 600 (тільки для власника)...\n");
    char cmd[256];
    sprintf(cmd, "sudo chown root %s && sudo chmod 600 %s", filename, filename);
    system(cmd);

    check_access(filename);

    return 0;
}
