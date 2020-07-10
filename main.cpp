#include "INode.h"
#include "File.h"
#include "FileSystem.h"
#include "OpenFileManager.h"
#include "FileManager.h"
#include "User.h"
#include <ctime>
#include <iostream>
#include <unordered_map>
#include <afxres.h>
#include "string"
using namespace std;

DeviceDriver g_DeviceDriver;
BufferManager g_BufferManager;
OpenFileTable g_OpenFileTable;
SuperBlock g_SuperBlock;
FileSystem g_FileSystem;
INodeTable g_INodeTable;
FileManager g_FileManager;
User g_User;

void man(string command) {

    static string man =
            "Command       :  man -��ʾ���߰����ֲ� \n"
            "Description   :  �����û�ʹ����Ӧ���� \n"
            "Usage         :  man [����] \n"
            "Parameter     :  [����] ���£�  \n"
            "                 man          :  �ֲ� \n"
            "                 fformat      :  ��ʽ�� \n"
            "                 exit         :  ��ȷ�˳� \n"
            "                 mkdir        :  �½�Ŀ¼ \n"
            "                 cd           :  �ı�Ŀ¼ \n"
            "                 ls           :  �г�Ŀ¼���ļ� \n"
            "                 create       :  �½��ļ� \n"
            "                 delete       :  ɾ���ļ� \n"
            "                 rmdir        :  ɾ���ļ��� \n"
            "                 open         :  ���ļ� \n"
            "                 close        :  �ر��ļ� \n"
            "                 seek         :  �ƶ���дָ�� \n"
            "                 write        :  д���ļ� \n"
            "                 read         :  ��ȡ�ļ� \n"
            "                 history      :  ��ʷ���� \n"
            "                 stat         :  �鿴�ļ���Ϣ \n"
            "                 adduser      :  �û�ע�� \n"
            "                 at|autoTest  :  �Զ����� \n"
            "Usage Demo    :  man mkdir \n"
    ;

    static string fformat =
            "Command       :  fformat -�����ļ�ϵͳ��ʽ�� \n"
            "Description   :  �������ļ�ϵͳ���и�ʽ��������������ļ���Ŀ¼! \n"
            "Usage         :  fformat \n"
            "Parameter     :  �� \n"
            "Usage Demo    :  fformat \n"
    ;

    static string exit =
            "Command       :  exit -�˳��ļ�ϵͳ \n"
            "Description   :  ��Ҫ�˳��������ͨ��exit�����ʱ�����˳����������������\n"
            "              :  �������ڴ���δ���µ������ϵĻ���ἰʱ���£���֤��ȷ�ԡ����� \n"
            "              :  �����ڹرհ�ť�����ڸ���ǰ�����ź�ǿ���˳���������������� \n"
            "              :  ����δд�ز�����Ϣ���ٴ�����ʱ���ܳ��ִ���! \n"
            "Usage         :  exit \n"
            "Parameter     :  �� \n"
            "Usage Demo    :  exit \n"
    ;

    static string mkdir =
            "Command       :  mkdir -����Ŀ¼ \n"
            "Description   :  �½�һ��Ŀ¼�������ִ��󣬻�����Ӧ������ʾ! \n"
            "Usage         :  mkdir <Ŀ¼��> \n"
            "Parameter     :  <Ŀ¼��> ���������·����Ҳ�����Ǿ���·�� \n"
            "Usage Demo    :  mkdir dirName \n"
            "                 mkdir ../dirName \n"
            "                 mkdir ../../dirName \n"
            "                 mkdir /dirName \n"
            "                 mkdir /dir1/dirName \n"
            "Error Avoided :  Ŀ¼��������Ŀ¼·�������ڣ�Ŀ¼������Ŀ¼�� \n"
    ;

    static string ls =
            "Command       :  ls -��Ŀ¼���� \n"
            "Description   :  �г���ǰĿ¼�а������ļ�����Ŀ¼���������ִ��󣬻�����Ӧ������ʾ! \n"
            "Usage         :  ls <Ŀ¼��> \n"
            "Parameter     :  <Ŀ¼��> Ĭ��Ϊ��ǰĿ¼��\n"
            "                 <Ŀ¼��> ���������·����Ҳ�����Ǿ���·�� \n"
            "Usage Demo    :  ls \n"
            "                 ls ../dirName \n"
            "                 ls ../../dirName \n"
            "                 ls /dirName \n"
            "                 ls /dir1/dirName \n"
            "Error Avoided :  Ŀ¼��������Ŀ¼·�������ڣ�Ŀ¼������Ŀ¼�� \n"
    ;

    static string cd =
            "Command       :  cd -�ı䵱ǰĿ¼ \n"
            "Description   :  �ı䵱ǰ����Ŀ¼�������ִ��󣬻�����Ӧ������ʾ! \n"
            "Usage         :  cd <Ŀ¼��> \n"
            "Parameter     :  <Ŀ¼��> Ĭ��Ϊ��ǰĿ¼��\n"
            "                 <Ŀ¼��> ���������·����Ҳ�����Ǿ���·�� \n"
            "Usage Demo    :  cd \n"
            "                 cd ../dirName \n"
            "                 cd ../../dirName \n"
            "                 cd /dirName \n"
            "                 cd /dir1/dirName \n"
            "Error Avoided :  Ŀ¼��������Ŀ¼·�������ڣ�Ŀ¼������Ŀ¼�� \n"
    ;

    static string create =
            "Command       :  create -�½��ļ� \n"
            "Description   :  �½�һ���ļ��������ִ��󣬻�����Ӧ������ʾ! \n"
            "Usage         :  create <�ļ���> <ѡ��> \n"
            "Parameter     :  <�ļ���> ���԰������·�������·�� \n"
            "                 <ѡ��> -r ֻ������ \n"
            "                 <ѡ��> -w ֻд���� \n"
            "                 <ѡ��> -rw == -r -w ��д���� \n"
            "Usage Demo    :  create newFileName -rw \n"
            "                 create ../newFileName -rw \n"
            "                 create ../../newFileName -rw \n"
            "                 create /newFileName -rw \n"
            "                 create /dir1/newFileName -rw \n"
            "Error Avoided :  �ļ���������Ŀ¼·�������ڣ�Ŀ¼������Ŀ¼�� \n"
    ;

    static string delet =
            "Command       :  delete -ɾ���ļ� \n"
            "Description   :  ɾ��һ���ļ��������ִ��󣬻�����Ӧ������ʾ! \n"
            "Usage         :  delete <�ļ���> \n"
            "Parameter     :  <�ļ���> ���԰������·�������·�� \n"
            "Usage Demo    :  delete fileName \n"
            "                 delete ../fileName \n"
            "                 delete ../../fileName \n"
            "                 delete /fileName \n"
            "                 delete /dir1/fileName \n"
            "Error Avoided :  ����ͨ�ļ����ļ���������Ŀ¼·�������ڣ�Ŀ¼������Ŀ¼�� \n"
    ;

    static string rmdir =
            "Command       :  rmdir -ɾ���ļ��� \n"
            "Description   :  ɾ��һ���ļ��С������ִ��󣬻�����Ӧ������ʾ! \n"
            "Usage         :  delete <�ļ�����> \n"
            "Parameter     :  <�ļ�����> ���԰������·�������·�� \n"
            "Error Avoided :  ���ļ��У��ļ������������ļ���·�������ڣ�Ŀ¼������Ŀ¼�� \n"
    ;

    static string open =
            "Command       :  open -���ļ� \n"
            "Description   :  ��Unix|Linux����open����һ���ļ�����Ҫ�����ļ��Ķ�д������open��\n"
            "                 �����ִ��󣬻�����Ӧ������ʾ! \n"
            "Usage         :  open <�ļ���> <ѡ��> \n"
            "Parameter     :  <�ļ���> ���԰������·�������·�� \n"
            "                 <ѡ��> -r ֻ������ \n"
            "                 <ѡ��> -w ֻд���� \n"
            "                 <ѡ��> -rw == -r -w ��д���� \n"
            "Usage Demo    :  open fileName -r \n"
            "                 open ../fileName -w \n"
            "                 open ../../fileName -rw \n"
            "                 open /fileName -r -w \n"
            "                 open /dir1/fileName -rw \n"
            "Error Avoided :  �ļ���������Ŀ¼·�������ڣ�Ŀ¼������Ŀ¼�� \n"
    ;

    static string close =
            "Command       :  close -�ر��ļ� \n"
            "Description   :  ��Unix|Linux����close���ر�һ���ļ������Զ��Ѿ��򿪵��ļ����йر� \n"
            "                 �����ִ��󣬻�����Ӧ������ʾ! \n"
            "Usage         :  close <file descriptor> \n"
            "Parameter     :  <file descriptor> �ļ������� \n"
            "Usage Demo    :  close 1 \n"
            "Error Avoided :  �ļ������������ڻ򳬳���Χ \n"
    ;

    static string seek =
            "Command       :  seek -�ƶ���дָ�� \n"
            "Description   :  ��Unix|Linux����fseek���ƶ���ǰһ���Ѿ��򿪵��ļ��Ķ�дָ�롣�����ִ��󣬻�����Ӧ������ʾ! \n"
            "Usage         :  seek <file descriptor> <offset> <origin> \n"
            "Parameter     :  <file descriptor> open���ص��ļ������� \n"
            "                 <offset> ָ��Ŀ��λ�ã���ʾĿ��λ������ʼλ��<origin>���ƫ���� �����ɸ� \n"
            "                 <origin> ָ����ʼλ�ã���Ϊ0(SEEK_SET), 1(SEEK_CUR), 2(SEEK_END) \n"
            "Usage Demo    :  seek 1 500 0 \n"
            "Error Avoided :  �ļ������������ڻ򳬳���Χ��δ��ȷָ������ \n"
    ;

    static string write =
            "Command       :  write -д���ļ� \n"
            "Description   :  ��Unix|Linux����write����ָ������д��һ���Ѿ��򿪵��ļ��С������ִ��󣬻�����Ӧ������ʾ! \n"
            "Usage         :  write <file descriptor> <InFileName> <size> \n"
            "Parameter     :  <file descriptor> open���ص��ļ������� \n"
            "                 <InFileName> ָ��д������Ϊ�ļ�InFileName�е����� \n"
            "                 <size> ָ��д���ֽ�������СΪ <size> \n"
            "Usage Demo    :  write 1 InFileName 123 \n"
            "Error Avoided :  �ļ������������ڻ򳬳���Χ��δ��ȷָ������ \n"
    ;

    static string read =
            "Command       :  read -��ȡ�ļ� \n"
            "Description   :  ��Unix|Linux����read����һ���Ѿ��򿪵��ļ��ж�ȡ�������ִ��󣬻�����Ӧ������ʾ! \n"
            "Usage         :  read <file descriptor> [-o <OutFileName>] <size> \n"
            "Parameter     :  <file descriptor> open���ص��ļ������� \n"
            "                 [-o <OutFileName>] -o ָ�������ʽΪ�ļ����ļ���Ϊ <OutFileName> ��ָ��-o����ʱĬ�������shell \n"
            "                 <size> ָ����ȡ�ֽ�������СΪ <size> \n"
            "Usage Demo    :  read 1 -o OutFileName 123 \n"
            "                 read 1 123 \n"
            "Error Avoided :  �ļ������������ڻ򳬳���Χ��δ��ȷָ������ \n"
    ;

    static string history =
            "Command       :  history -��ȡ��ʷ���� \n"
            "Description   :  ��ӡȫ����ʷ���� \n"
            "Usage         :  history \n"
            "Usage Demo    :  history \n"
            "Error Avoided :  history�ļ��𻵶����µĶ�ȡʧ�� \n"
    ;

    static string stat =
            "Command       :  stat -��ȡ�ļ����� \n"
            "Description   :  ��ȡָ���ļ����ļ���С����ϸ��Ϣ \n"
            "Usage         :  stat <�ļ�����> \n"
            "Parameter     :  <�ļ���> ���԰�������·����Ŀ¼���ļ� \n"
            "Error Avoided :  �ļ������������ļ���·�������ڣ�Ŀ¼������Ŀ¼�� \n"
    ;

    static string autoTest =
            "Command       :  autoTest -�Զ����� \n"
            "Description   :  �������ԣ���ϵͳ�������ڰ������ԡ����Բ�һ�������������ȷ�ģ�����ϵͳ�����ݴ��ԣ�\n"
            "              :  ����ʹϵͳ�쳣��\n"
            "Usage         :  autoTest | at \n"
            "Parameter     :  �� \n"
            "Usage Demo    :  at \n"
    ;

    static string logout =
            "Command       :  logout \n"
            "Description   :  �ǳ��û���\n"
            "              :  ����ʹϵͳ�쳣��\n"
            "Usage         :  logout \n"
            "Parameter     :  �� \n"
    ;

    static string adduser =
            "Command       :  adduser \n"
            "Description   :  ����û���\n"
            "              :  ����ʹϵͳ�쳣��\n"
            "Usage         :  adduser [name] [passwd] \n"
            "Parameter     :  �� \n"
    ;
    static unordered_map<string, string*>manMap({
                                                        { "man", &man },
                                                        { "at", &autoTest },
                                                        { "fformat", &fformat },
                                                        { "exit", &exit },
                                                        { "mkdir", &mkdir },
                                                        { "cd", &cd },
                                                        { "ls", &ls },
                                                        { "create", &create },
                                                        { "delete", &delet },
                                                        { "open", &open },
                                                        { "close", &close },
                                                        { "seek", &seek },
                                                        { "write", &write },
                                                        { "read", &read },
                                                        { "autoTest", &autoTest },
                                                        {"history", &history},
                                                        {"rmdir", &rmdir},
                                                        {"stat", &stat},
                                                        {"logout", &logout},
                                                        {"adduser", &adduser}
                                                });

    auto it = manMap.find(command);
    if (it == manMap.end()) {
        cout << "shell : " << command << " : don't find this commond \n";
        return;
    }
    cout << *it->second;
}

bool autoTest(string& cmd) {
    static int testNo = 0;
    static char* testCmds[] = {
            //"ls",
            //"cd dir1",
            //"cd /",
            //"cd dir1/dir11",
            //"ls",
            //"cd ../dir11/dir111",
            //"ls",
            //"cd /",
            //"ls",

            "mkdir /dir1",
            "mkdir dir2",
            "create file1 -rw",
            "create file2 -rw",
            "ls",
            "delete /file2",
            "ls",
            "mkdir /dir1/dir11",
            "create /dir1/file11 -rw",
            "cd dir1",
            "ls",
            "cd ..",
            "ls",
            "open file1 -rw",
            "write 6 file1-2000.txt 800",
            "seek 6 500 0",
            "read 6 20",
            "seek 6 500 0",
            "read 6 -o readOut1.txt 20",
            "seek 6 -20 1",
            "read 6 100",
            "close 6",
            "cd dir1",
            "ls",
            "open file11 -rw",
            "write 6 file11-100000.txt 100000",
            "seek 6 0 0",
            "read 6 100",
            "read 6 100",
            "seek 6 50000 0",
            "read 6 100"
    };
    int cmdNums = sizeof(testCmds) / sizeof(char*);
    cmd = testCmds[testNo % cmdNums];
    return ++testNo <= cmdNums;
}

void cmdArgs(const string& cmd, vector<string>& args) {
    args.clear();
    string str;
    unsigned int p, q;
    for (p = 0, q = 0; q < cmd.length(); p = q + 1) {
        q = cmd.find_first_of(" \n", p);
        str = cmd.substr(p, q - p);
        if (!str.empty()) {
            args.push_back(str);
        }
        if (q == string::npos)
            return;
    }
}

int main() {
    User* user = &g_User;
    string line = "";
    vector<string> args;
    string cmd, arg1, arg2, arg3;
    int autoFlag = 0;

    fstream fileOut;
    fileOut.open("./history", ios::app);
    if (!fileOut.good())
    {
        cerr << "��ȡ�ļ�����" << endl;
    }
    cout << "++++++++++++++++++++ Unix�ļ�ϵͳģ�� ++++++++++++++++++++" << endl;

    // ��¼ϵͳ
    string name = "", psswd = "";
    while (1){
        if (line == ""){
            goto NEXT;
        }
        cmdArgs(line, args);
        cmd = args[0];
        arg1 = args.size() > 1 ? args[1] : "";
        arg2 = args.size() > 2 ? args[2] : "";
        arg3 = args.size() > 3 ? args[3] : "";
        if(cmd=="exit"){
            exit(0);
        }
        if(name==""){
            name = cmd;
        }else{
            psswd = cmd;
        }

        NEXT:
        bool canin = false;
        if (name==""){
            cout<<"please input user name or exit: ";
        }else if(psswd==""){
            cout<<name<<" password is: ";
        }else{
            ifstream infile;
            infile.open("./passwd", ios::in);
            if (!infile.good()){
                cout<<"�û��ļ���ʧ�������˳�"<<endl;
                exit(0);
            }
            while (getline(infile, line)){
                if (line.size()==0){
                    cout<<"error name, please try again!\n";
                    name = "";
                    psswd = "";
                    goto NEXT;
                }
                std::size_t mid = line.find(" ", 0);
                string true_name = line.substr(0, mid);
                string true_passwd = line.substr(mid+1, line.size()-mid-1);
                if (name != true_name) continue;
                if (psswd != true_passwd){
                    cout<<"error password! please try again!\n"<<endl;
                    name = "";
                    psswd = "";
                    goto NEXT;
                }
                if (psswd == true_passwd && name == true_name) {
                    canin = true;
                    user->username = true_name;
                    break;
                }
            }
            infile.close();
            if (!canin){
                cout<<"error name, please try again!\n";
                name = "";
                psswd = "";
                goto NEXT;
            }
        }
        if (canin) break;
        getline(cin, line);

    }
    cout<<"Command       :  man -��ʾ���߰����ֲ� \n"
          "Description   :  �����û�ʹ����Ӧ���� \n"
          "Usage         :  man [����] \n"
          "Parameter     :  [����] ���£�  \n"
          "                 man          :  �ֲ� \n"
          "                 fformat      :  ��ʽ�� \n"
          "                 exit         :  ��ȷ�˳� \n"
          "                 mkdir        :  �½�Ŀ¼ \n"
          "                 cd           :  �ı�Ŀ¼ \n"
          "                 ls           :  �г�Ŀ¼���ļ� \n"
          "                 create       :  �½��ļ� \n"
          "                 delete       :  ɾ���ļ� \n"
          "                 rmdir        :  ɾ���ļ��� \n"
          "                 open         :  ���ļ� \n"
          "                 close        :  �ر��ļ� \n"
          "                 seek         :  �ƶ���дָ�� \n"
          "                 write        :  д���ļ� \n"
          "                 read         :  ��ȡ�ļ� \n"
          "                 history      :  ��ʷ���� \n"
          "                 at|autoTest  :  �Զ����� \n"
          "                 stat         :  ��ȡ�ļ���Ϣ \n"
          "                 logout       :  �û��ǳ� \n"
          "                 adduser      :  ����û� \n"
          "Usage Demo    :  man mkdir \n";

    line = "";
    while (1) {
        if (line == "")
            goto NEXT_INPUT;

        cmdArgs(line, args);
        cmd = args[0];
        arg1 = args.size() > 1 ? args[1] : "";
        arg2 = args.size() > 2 ? args[2] : "";
        arg3 = args.size() > 3 ? args[3] : "";

        if (cmd== "man" || cmd=="fformat" || cmd == "exit" || cmd == "at" || cmd == "autoTest"
            || cmd == "mkdir" || cmd == "ls" || cmd == "cd" || cmd == "create" || cmd == "delete"
            || cmd == "open" || cmd == "close" || cmd == "seek" || cmd == "read" || cmd == "write"
            || cmd == "history" || cmd == "rmdir" || cmd == "stat" || cmd == "adduser"
                ){
            fileOut<<line<<"\n";
            fileOut.flush();
        }

        if (cmd == "man") {
            man(arg1.empty() ? "man" : arg1);
        }
        else if (cmd == "fformat") {
            g_OpenFileTable.Format();
            g_INodeTable.Format();
            g_BufferManager.FormatBuffer();
            g_FileSystem.FormatDevice();
            cout<<"Filesystem formatted successfully.\nwaiting to exit...";
            Sleep(3000);
            exit(0);
        }
        else if (cmd == "exit") {
            fileOut.close();
            exit(0);
        }
        else if (cmd == "at" || cmd == "autoTest") {
            autoFlag = 1;
            cout << "autoTest begin ... \njust press enter to continue ... \n" ;
        }
        else if (cmd == "mkdir") {
            user->Mkdir(args[1]);
        }
        else if (cmd == "ls") {
            if (arg1!=""){
                user->Ls(arg1);
            }else{
                user->Ls();
            }
        }
        else if (cmd == "cd") {
            user->Cd(arg1);
        }
        else if (cmd == "create") {
            //create û����Ҫģʽ�ı�Ҫ
            user->Create(arg1, arg2 + arg3);
        }
        else if (cmd == "delete") {
            user->Delete(arg1);
        }
        else if (cmd == "rmdir") {
            user->Rmdir(arg1);
        }
        else if (cmd == "open") {
            user->Open(arg1, line);
        }
        else if (cmd == "close") {
            user->Close(arg1);
        }
        else if (cmd == "seek") {
            user->Seek(arg1, arg2, arg3);
        }
        else if (cmd == "read") {
            if (arg2 == "-o")
                user->Read(arg1, arg3, args[4]);
            else
                user->Read(arg1, "", arg2);
        }
        else if (cmd == "write") {
            user->Write(arg1, arg2, arg3);
        }
        else if (cmd == "history"){
            user->History();
        }
        else if (cmd == "stat"){
            user->Stat(arg1);
        }
        else if (cmd == "logout"){
            name = "";
            psswd = "";
            goto NEXT;
        }
        else if (cmd == "adduser"){
            if(arg1==""||arg2==""){
                cout<<"please input full name adn password !"<<endl;
                goto NEXT_INPUT;
            }
            fstream passwdOut;
            passwdOut.open("./passwd", ios::app);
            if (!fileOut.good())
            {
                cerr << "��ȡ�ļ�����" << endl;
            }
            passwdOut<<arg1<<" "<<arg2<<"\n";
            passwdOut.flush();
            passwdOut.close();
            cout<<arg1<<" registered successfully!\n";
        }
        else if (cmd != "") {
            cout << "shell : " << cmd << " : don't find this commond \n";
        }

        NEXT_INPUT:
        cout << "[unix-fs " << user->curDirPath << " ]$ ";
        if (autoFlag) {
            if (autoTest(line)) {
                cout << line;
                getchar();
            }
            else {
                cout << "autoTest finished ... \n";
                autoFlag = 0;
                line = "";
            }
        }
        else {
            getline(cin, line);
        }
    }
    return 0;
}