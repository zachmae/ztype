# Client

-1 = disconect
0 = ??
1 = pos client

# Server
- to NewClient
    - id;

- to EveryOldClient
    - "new_client" >> id;

- to NewClient
    - "old_client" >> number >> c1_id  >> ...;

- to EveryClientexceptTheSender
    - "client_pos" >> id >> x >> y;