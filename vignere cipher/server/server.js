const { Server } = require("socket.io");
const PORT = 3000

const io = new Server(PORT);

io.on('connection', client => {
    console.log('client connected', client.id);
    client.on('message-sent', data => {
        
        // const len = data.length;
        // decrypt
        console.log('Encrypted text: ', data.encryptedText);
        // console.log(data);
        let res = decrypt(data.encryptedText, data.key);
        console.log(`Decrypted Text:`, res);
        io.emit('message-received', {id: client.id, message: data});
    });
    client.on('disconnect', () => {
        console.log('Client disconnected');
    });
});

function decrypt (s, key) {
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

    key = key.toUpperCase();
    let newKey = "";
    let noOfTimes = Math.floor(msgLen / keyLen);
    
    for (let i=0; i<noOfTimes; i++)
        newKey += key;
    
    let len = msgLen - newKey.length;
    
    for (let i=0; i<len; i++)
        newKey += key[i];
    
    let decrypted = "";
    for (let i=0; i<msgLen; i++) {
        if (!(/^[a-zA-Z]+$/.test(s[i])))        // alphabet check
            decrypted += s[i];
        else {
            let row = cipher[newKey.charCodeAt(i)-65];          // for the newkey elements, we find the row
            let idx = row.indexOf(s[i]);                        // we then find the index of the message character one by one
            decrypted += alphabets[idx];
        }
    }
    return decrypted;
}