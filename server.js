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
    const len = s.length;
    var rails = new Array(key);
    for (let i=0; i<key; i++) {
        rails[i] = new Array(len);
    }
 
    for (let i=0; i<key; i++)
        for (let j=0; j<len; j++)
            rails[i][j] = '@';
 
    let isDirectionDown = false;
 
    let row = 0, col = 0;
 
    for (let i=0; i < len; i++) {
        if (row == 0)
            isDirectionDown = true;
        if (row == key-1)
            isDirectionDown = false;
 
        
        rails[row][col++] = '~';        
        isDirectionDown ? row++ : row--;
    }
 
    let idx = 0;
    for (let i=0; i<key; i++)
        for (let j=0; j<len; j++)
            if (rails[i][j] == '~' && idx<len)
                rails[i][j] = s[idx++];
 
    let result = "";
 
    row = 0, col = 0;
    for (let i=0; i<len; i++) {
        if (row == 0)
            isDirectionDown = true;
        if (row == key-1)
            isDirectionDown = false;
 
        if (rails[row][col] != '~')
            result += rails[row][col++];
 
        isDirectionDown ? row++: row--;
    }
    return result;
}


