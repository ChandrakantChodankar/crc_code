#include <iostream>
using namespace std;

string xorfun(string encode, string crc)
{
    int crclen = crc.length();
    for (int i = 0; i <= (encode.length() - crclen);)
    {
        for (int j = 0; j < crclen; j++)
        {
            encode[i + j] = encode[i + j] == crc[j] ? '0' : '1'; // does xor operation 0 xor 0 is 0, 1 xor 1 is 0
        }                                                       // 1 xor 0 is 1, 0 xor 1 is 1 
        for (; i < encode.length() && encode[i] != '1'; i++)
            ;
    }
    return encode;
}

int main()
{
    string msg, data, crc, encode;
    cout << "sender side" << endl;
    cout << "Enter the data";
    cin >> data;
    cout << "Enter the crc code";
    cin >> crc;

    encode += data;   //add data to encode
    int datalen = data.length(); //data length 
    int crclen = crc.length();   //crc length

    for (int i = 1; i <= (crclen - 1); i++) //insert crclen-1 0's in encode
        encode += '0';

    encode = xorfun(encode, crc);
    cout << "check generated is: ";
    cout << encode.substr(encode.length() - crclen + 1) << endl; // display the last remaining bits
    cout << "message to be transmitted: `";
    cout << data + encode.substr(encode.length() - crclen + 1); // show the message to be sent bby adding the data string and aove remaig bits 

    cout << "\nReceiver side" << endl;
    cout << "Enter the message: ";
    cin >> msg;

    msg = xorfun(msg, crc);
    for (char i : msg.substr(msg.length() - crclen + 1))
    {
        if (i != '0') // checks if there is 0 in the message if 0 is not present then error in message
        {
            cout << "Error in message" << endl;
            return 0;
        }
    }
    cout << "No error in message";
    return 0;
}