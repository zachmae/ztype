# Client

- to Server
    - "disconect"
    - "pos_client" >> _id >> x >> y

# Server
- to NewClient
    - id;

- to EveryOldClient
    - "new_client" >> id;

- to NewClient
    - "old_client" >> number >> c1_id  >> ...;

- to EveryClientexceptTheSender
    - "client_pos" >> id >> x >> y;

# ...

ships shouldn't be able to kill themselves..