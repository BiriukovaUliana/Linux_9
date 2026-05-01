const { exec } = require('child_process');

// Виконуємо команду через sudo
// Це дозволить прочитати /etc/shadow, навіть якщо скрипт запущено від звичайного користувача
exec('sudo cat /etc/shadow', (error, stdout, stderr) => {
    if (error) {
        console.error("Помилка доступу: Переконайтеся, що у вас є права sudo.");
        console.error(stderr);
        return;
    }

    console.log("--- Вміст файлу /etc/shadow (перші 5 рядків) ---");
    // Виведемо лише частину файлу, щоб не захаращувати термінал
    const lines = stdout.trim().split('\n').slice(0, 5);
    lines.forEach(line => console.log(line));
});
