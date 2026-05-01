const { execSync } = require('child_process');
const fs = require('fs');

const fileName = 'original.txt';
const copyName = 'root_copy.txt';

try {
    fs.writeFileSync(fileName, 'Hello World');
    console.log('1. Файл створено.');

    execSync('sudo cp ' + fileName + ' ' + copyName);
    console.log('2. Файл скопійовано від імені root.');

    try {
        fs.appendFileSync(copyName, '\nNew Data');
        console.log('3. Зміна: Успішно');
    } catch (e) {
        console.log('3. Зміна: Помилка');
    }

    try {
        execSync('rm ' + copyName);
        console.log('4. Видалення: Успішно');
    } catch (e) {
        console.log('4. Видалення: Помилка');
    }

} catch (err) {
    console.error('Помилка sudo:', err.message);
}
