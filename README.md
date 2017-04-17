# A Distributed, Sharded Key-Value Store
## Written in C++, backed by Paxos

Isaac Bowen(irbowen) & Pranav Ramarao(pranavr)

Our paxos implmentation is written in c++14. 
You can get started with 

```bash
git@github.com:irbowen/Sharded_Key_Value_Store.git
cd Sharded_Key_Value_Store

# generate config files based on #shards and #tolerated failures
python make_scripts.py

make
./scripts/start_master.sh; ./scripts/start_replicas.sh 
```
This will build the binares for the key-value/paxos replicas, the master, and all of the test clients.
You can see all the running processes with

```bash
./scripts/show_all.sh
```

