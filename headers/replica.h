
#ifndef replica_h
#define replica_h

#include <condition_variable>
#include <fstream>
#include <iostream>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

#include "acceptor.h"
#include "learner.h"
#include "network.h"
#include "proposer.h"
#include "kv_store.h"

class replica {
private:
    mutex m;
    // server info
    int port;
    std::string host;

    // replica id
    int id;

    // holes that we need to simulate
    vector<int> seq_holes;

    // holes that we need to simulate
    set<int> seen_views;

    // current view number that this replica thinks it is in
    int cur_view_num = -1;

    // total number of replicas in the system
    size_t num_replicas = 0;

    network net;

    bool is_seq_hole(int seq);

    // list of replicas in the system
    std::vector<node> replicas;
    std::map<int, node> seq_to_client_map;

    /* Mapping from client_id to the latest client sequence number that got finished */
    std::map<string, int> client_progress_map;

    void handle_msg(Message*);
    void handle_kv_msg(Message*);

    /* Adds all the replicas in the system to the receiver list of the reply message */
    void make_broadcast(Message *reply);

    /* Replica can perform all of the following roles
       in its paxos component */
    Acceptor acceptor;
    Proposer proposer;
    Learner learner;

    /* Replica also runs the key value server in another thread */
    std::unique_ptr<KV_Store> kv_store_;

public:
    bool is_primary(int view_num);
    bool is_previous_view(int view_num);

    replica(int _port, std::string _host, int _id, std::string _config_file, std::string _holes_file);
    void start();
    void recv();
    void kv_recv();
};

#endif
