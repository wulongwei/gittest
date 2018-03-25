#include "cli.h"

static int parse = 0;
//利用freeRTOS发送一个信号单独处理解析命令。中断不处理，抛给进程
void itnputOver(void){
    
    parse = 1;
}

void doShowGateway(char ** arg){
    
    logInfoFL("\r\n");
    return;
}

void doShowNodeInfo(char ** arg){
    
    logInfoFL("\r\n");
    return;
}

void doShowNodeStat(char ** arg){
    
    logInfoFL("\r\n");
    return;
}

const cliCmd_t cliCmdShow = {
    .cmdName = "show",
    .havaSubCmd = 1,
    .help = NULL,
    .maxArg = 0,
    .cmdUsage = NULL,
    .arg1 = argTypeNotUse,
    .doCmd = NULL,
};

const cliCmd_t cliCmdShowGateway = {
    .cmdName = "gateway",
    .havaSubCmd = 0,
    .help = "show gateway info",
    .maxArg = 0,
    .cmdUsage = "gateway",
    .arg1 = argTypeNotUse,
    .doCmd = doShowGateway,
};

const cliCmd_t cliCmdShowNode = {
    .cmdName = "node",
    .havaSubCmd = 1,
    .help = NULL,
    .maxArg = 0,
    .cmdUsage = NULL,
    .arg1 = argTypeNotUse,
    .doCmd = NULL,
};
const cliCmd_t cliCmdShowNodeInfo = {
    .cmdName = "info",
    .havaSubCmd = 0,
    .help = "show node info",
    .maxArg = 1,
    .cmdUsage = "node info [command]",
    .arg1 = argTypeInt,
    .doCmd = doShowNodeInfo,
};
const cliCmd_t cliCmdShowNodeStat = {
    .cmdName = "stat",
    .havaSubCmd = 0,
    .help = "show node stat",
    .maxArg = 1,
    .cmdUsage = "help [command]",
    .arg1 = argTypeInt,
    .doCmd = doShowNodeStat,
};


int main(int argc,char ** argv){

    int r;

    logInit(logLevelDebug);
    r = cliCmdInit(itnputOver);
    
    cliCmdRegister("/",(pcliCmd_t)&cliCmdShow);
        cliCmdRegister("/show",(pcliCmd_t)&cliCmdShowGateway);
        cliCmdRegister("/show",(pcliCmd_t)&cliCmdShowNode);
            cliCmdRegister("/show/node",(pcliCmd_t)&cliCmdShowNodeInfo);
            cliCmdRegister("/show/node",(pcliCmd_t)&cliCmdShowNodeStat);
    if(2 == argc){
        for(r = 0;r < strlen(argv[1]);r++) cliCmdCharRx(argv[1][r]);
    }
    cliCmdCharRx('\n');
    while(0 == parse);
    cliCmdParse();
}
