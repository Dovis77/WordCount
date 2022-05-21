// Wordcount.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <stdio.h>
#include <unistd.h>

int lineCount = 0;  // 总行数
int charCount = 0;  // 总字符数
int wordCount = 0;  //总单词数 
int a = 0, l = 0, w = 0, c = 0;
int main(int argc, char* argv[]) {
    char fname[] = "D:/学习/现代软件工程/input.txt";
    char opt;
    while ((opt = getopt(argc, argv, "a:l:w:c:")) != -1)
    {
        switch (opt)
        {
            //-a 指令显示字符数，单词数，行数 
        case 'a':
            l = w = c = 1;
            //strcpy(inputFileName,optarg);
            break;
            //-l 指令显示行数 
        case 'l':
            l = 1;
            //strcpy(inputFileName,optarg);
            break;
            //-w 指令显示单词数 
        case 'w':
            w = 1;
            //strcpy(inputFileName,optarg); 
            break;
            //-c 指令显示字符数 
        case 'c':
            c = 1;
            //strcpy(inputFileName,optarg);
            break;
        }
    }
    countFile(fname);
    //writeOutput(outputFileName, inputFileName);

    return 0;
}
int countFile(char* filename) {
    FILE* fp;  // 指向文件的指针
    char buffer[1000];  //缓冲区，存储读取到的每行的内容
    int bufferLength;  // 缓冲区中实际存储的内容的长度
    int i;  // 当前读到缓冲区的第i个字符
    char ch;  // 读取到的字符
    int isBlank = 0;  // 上个字符是否是空格
    int charNumber = 0;  // 当前行的字符数
    int wordNumber = 0; // 当前行的单词数

    if ((fp = fopen(filename, "rb")) == NULL) {
        perror(filename);
        return -1;
    }
    // 每次读取一行数据，保存到buffer，每行最多只能有1000个字符
    while (fgets(buffer, 1000, fp) != NULL) {
        bufferLength = strlen(buffer);
        // 遍历缓冲区的内容
        for (i = 0; i < bufferLength; i++) {
            ch = buffer[i];
            if (ch == ' ' || ch == '\t') {  // 遇到空格
                !isBlank && wordNumber++;  // 如果上个字符不是空格，那么单词数加1
                isBlank = 1;
            }
            else if (ch != '\n' && ch != '\r') {  // 忽略换行符
                charNumber++;  // 如果既不是换行符也不是空格，字符数加1
                isBlank = 0;
            }
        }
        !isBlank && wordNumber++;  // 如果最后一个字符不是空格，那么单词数加1
        isBlank = 1;  // 每次换行重置为1
        // 一行结束，计算总字符数、总单词数、总行数
        lineCount++;  // 总行数
        charCount += charNumber;  // 总字符数
        wordCount += wordNumber;  // 总单词数
        // 置零，重新统计下一行
        charNumber = 0;
        wordNumber = 0;
    }
    if (c)
    {
        printf("字符数:%d", charCount);
    }
    if (w)
    {
        printf("单词数:%d", wordCount);
    }
    if (l)
    {
        printf("行数:%d", lineCount);
    }

    if (c == 0 && w == 0 && l == 0) {
        printf("统计失败");
    }

    fclose(fp);
    return 1;
}


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
