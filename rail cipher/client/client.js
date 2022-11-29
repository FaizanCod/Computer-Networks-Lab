const { io } = require("socket.io-client");
const socket = io('http://localhost:3000')
const readline = require('node:readline')
const { stdin: input, stdout: output } = require('node:process');

const clientInfo = {
    name: ""
}

// This is the client side code
var start = true;

const sendService = () => {
    let rl = readline.createInterface({ input, output });
    if (start === true) {
        console.log('Successfully connected to server...');
        start = false;
        rl.question(`Enter your name: `, (clientName) => {
            readline.moveCursor(process.stdout, 0, -1);
            readline.clearLine(process.stdout, 1);
            console.log(`Hello ${clientName}!`);
            clientInfo.name = clientName;
            rl.close(); 
            setTimeout(() => sendService(), 300)
        });
    }
    rl.question('Enter encryption key: ', key => {
        readline.moveCursor(process.stdout, 0, -1);
        readline.clearLine(process.stdout, 1);
        rl.question('> ', msg => {
            readline.moveCursor(process.stdout, 0, -1);
            readline.clearLine(process.stdout, 1);
            let encryptedText = encrypt(msg, key);
            socket.emit('message-sent', { clientInfo, encryptedText, key });
            rl.close();
            setTimeout(() => sendService(), 300);
    
        });
    })
    
}

socket.on('message-received', (data) => {

    // if (data.id != socket.id) {
    //     readline.moveCursor(process.stdout, 0, -1);
    //     readline.clearLine(process.stdout, 0);
    //     console.log(`${data.message.clientInfo.name}: ${data.message.encryptedText}`);
    //     console.log('> ');
    // } else {
    //     console.log(`You: ${data.message.encryptedText}`)
    // }
    console.log(`Message successfully sent to Server!`);
});

function encrypt (s, key) {
    const len = s.length;
    var isDirectionDown = false;
    var rails = new Array(key);
    for (let i=0; i<key; i++) {
        rails[i] = new Array(len);
    }
    for (let i=0; i<key; i++) {
        for (let j=0; j<len; j++)
            rails[i][j] = '@';
    }
    
    let r = 0, c = 0;
    for (let j=0; j<len; j++) {
        if (r === 0 || r === key-1)
            isDirectionDown = !isDirectionDown;

        rails[r][c++] = s[j];

        isDirectionDown ? r++ : r--;
    }
    // for (let i=0; i<key; i++) {
    //     for (let j=0; j<len; j++) {
    //         process.stdout.write(rails[i][j]);
    //     }
    //     console.log();
    // }
    let encryptedText = "";
    for (let i=0; i<key; i++) {
        for (let j=0; j<len; j++) {
            if (rails[i][j] !== '@') {
                    // console.log(rails[i][j]);
                encryptedText += rails[i][j];
            }
        }
    }
    // console.log(encryptedText);
    return encryptedText;
}

sendService();