const { exec } = require('child_process');

exec('getent passwd', (error, stdout) => {
    if (error) {
        console.error("Помилка виконання: " + error.message);
        return;
    }

    const currentUser = process.env.USER;
    const minUid = 1000;
    const lines = stdout.trim().split('\n');

    console.log("--- Інші звичайні користувачі (UID >= " + minUid + ") ---");

    let found = false;
    lines.forEach(line => {
        const parts = line.split(':');
        const username = parts[0];
        const uid = parseInt(parts[2]);

        if (uid >= minUid && username !== currentUser) {
            console.log("Користувач: " + username + " (UID: " + uid + ")");
            found = true;
        }
    });

    if (!found) console.log("Крім вас, інших звичайних користувачів не знайдено.");
});
