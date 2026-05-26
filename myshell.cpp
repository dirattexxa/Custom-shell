#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <unistd.h>
#include <sys/wait.h>

std::vector<std::string> split_line(const std::string &line) {
    std::vector<std::string> tokens;
    std::string token;
    std::stringstream ss(line);
    while(ss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

int launch(const  std::vector<std::string> & args) {
    pid_t pid;
    pid_t wpid;
    int status;

    std::vector<char*> c_args;
    for(const auto& arg:args) {
        c_args.push_back(const_cast<char*>(arg.c_str()));
    }
    c_args.push_back(nullptr);
    pid = fork();

    if (pid == 0 ) {
        if(execvp(c_args[0], c_args.data()) == -1){
            std::perror("lsh");
        }
        exit(EXIT_FAILURE);
    }
    else if(pid < 0){
        std::perror("fork error");
    }
    else{
        do{
            wpid = waitpid(pid, &status, WUNTRACED);
        }
        while(!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}

void lsh_loop() {
    std::string line;
    while(true) {
        std::cout << "Daunshell >";
        if(!std::getline(std::cin, line)) break;
        if(line.empty()) continue;
        if(line == "exit") break;

        std::vector<std::string> args = split_line(line);

        launch(args);
    }
}
int main() {
    lsh_loop();
    return 0;
}