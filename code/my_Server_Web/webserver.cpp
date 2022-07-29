//
// Created by 86353 on 2022/7/19.
//

#include "webserver.h"

WebServer::WebServer() {

}

WebServer::~WebServer() {

}

void WebServer::init(int port, std::string user, std::string passWord, std::string databaseName, int log_write,
                     int opt_linger, int trigmode, int sql_num, int thread_num, int close_log, int actor_model) {

}

void WebServer::thread_pool() {

}

void WebServer::sql_pool() {

}

void WebServer::log_write() {

}

void WebServer::trig_mode() {

}

void WebServer::eventListen() {

}

void WebServer::eventLoop() {

}

void WebServer::timer(int connfd, struct sockaddr_in client_address) {

}

bool WebServer::dealclinetdata() {
    return false;
}

bool WebServer::dealwithsignal(bool &timeout, bool &stop_server) {
    return false;
}

void WebServer::dealwithread(int sockfd) {

}

void WebServer::dealwithwrite(int sockfd) {

}
