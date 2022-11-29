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
    const msgLen = s.length;
    const keyLen = key.length;

    var cipher = new Array(26);
    for (let i=0; i<26; i++) {
        cipher[i] = new Array(26);
    }
    let alphabets = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (let i=0; i<26; i++) {
        for (let j=0; j<26; j++) {
            cipher[i][j] = (alphabets[(i+j)%26]);
        }
    }

    s = s.toUpperCase();
    key = key.toUpperCase();
    let newKey = "";

    // while (newKey.length < msgLen)
    //     newKey += key;
    
    let noOfTimes = Math.floor(msgLen / keyLen);
    // console.log(noOfTimes);
    for (let i=0; i<noOfTimes; i++)
        newKey += key;
    
    let len = msgLen - newKey.length;
    // console.log(len);
    for (let i=0; i<len; i++)
        newKey += key[i];

    // console.log(newKey);
    
    let encrypted = "";
    for (let i=0; i<msgLen; i++) {
        if (!(/^[a-zA-Z]+$/.test(s[i])))
            encrypted += s[i];
        else                    // row corresponds to the iteration of the newKey, while the message iterates over to the column
            encrypted += cipher[newKey.charCodeAt(i)-65][s.charCodeAt(i)-65];
    }
    // console.log(encrypted);
    return encrypted;
}

sendService();