#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void show_dir_info(char *path) {
    printf("\n--- Вміст та права доступу у: %s ---\n", path);
    pid_t pid = fork();
    if (pid == 0) {
        execlp("ls", "ls", "-l", path, NULL);
        exit(0);
    } else {
        wait(NULL);
    }
}

void try_access(char *filepath) {
    printf("\nСпроба доступу до: %s\n", filepath);
    
    if (access(filepath, R_OK) == 0) printf("- Читання: ТАК\n");
    else printf("- Читання: НІ (Access Denied)\n");

    if (access(filepath, W_OK) == 0) printf("- Запис: ТАК\n");
    else printf("- Запис: НІ (Access Denied)\n");

    if (access(filepath, X_OK) == 0) printf("- Виконання: ТАК\n");
    else printf("- Виконання: НІ (Access Denied)\n");
}

int main() {
    // 1. Перегляд власників та прав у різних каталогах
    show_dir_info(".");         // Домашній (поточний) каталог
    show_dir_info("/usr/bin");  // Системні бінарні файли
    show_dir_info("/etc");     // Конфігураційні файли

    // 2. Спроби "обійти" права та перевірити доступ до різних власників
    printf("\n=== ТЕСТУВАННЯ ОБМЕЖЕНЬ ДОСТУПУ ===\n");
    
    // Файл у домашньому каталозі (власник - користувач)
    try_access("task96.c");
    
    // Системний файл (власник - root, зазвичай дозволено читання/виконання)
    try_access("/usr/bin/ls");
    
    // Критичний системний файл (власник - root, доступ обмежено)
    try_access("/etc/shadow");

    return 0;
}
