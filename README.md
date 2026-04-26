# 🚀 Mini Redis – Multithreaded Key-Value Store in C

A high-performance in-memory key-value store built from scratch in **C**, inspired by Redis.
This project demonstrates low-level system design concepts including **TCP networking, multithreading, custom data structures, and cache eviction policies**.

---

## 📌 Features

* ⚡ **TCP-based Client-Server Architecture**
* 🧵 **Multithreaded Server** using POSIX threads (`pthread`)
* 🗂️ **Custom HashMap** with collision handling (chaining)
* 🔁 **LRU (Least Recently Used) Cache Eviction**
* 🧠 **O(1) Operations** for SET, GET, DELETE
* 🔍 Command parsing and execution engine
* 🧩 Modular code structure (server, parser, commands, storage)

---

## 🛠️ Tech Stack

* **Language:** C
* **Networking:** TCP Socket Programming (POSIX)
* **Concurrency:** POSIX Threads (`pthread`)
* **Data Structures:** HashMap, Doubly Linked List
* **System Concepts:** Multithreading, Synchronization, Memory Management

---

## ⚙️ Supported Commands

| Command         | Description            |
| --------------- | ---------------------- |
| `SET key value` | Insert or update a key |
| `GET key`       | Retrieve value         |
| `DEL key`       | Delete key             |
| `EXISTS key`    | Check if key exists    |
| `INFO`          | Display system stats   |

---

## 🧠 How It Works

### 🔹 Data Storage

* Uses a **HashMap** for fast key-value access
* Handles collisions using **linked list chaining**

### 🔹 LRU Cache

* Implemented using a **Doubly Linked List**
* Tracks most/least recently used keys
* Evicts least recently used key when capacity is reached

### 🔹 Multithreading

* Each client connection is handled by a **separate thread**
* Shared resources protected using **mutex locks**

---

## ▶️ How to Run

### 1. Compile Server

```bash
gcc src/main.c src/server/server.c src/parser/parser.c \
src/hashmap/hashmap.c src/lru/lru.c src/commands/commands.c \
-o server -lpthread
```

### 2. Run Server

```bash
./server
```

### 3. Compile Client

```bash
gcc tests/main.c tests/client.c -o client
```

### 4. Run Client

```bash
./client
```

---

## 🧪 Example Usage

```
SET name argha
GET name
DEL name
EXISTS name
```

---

## 🏗️ Future Improvements

* 💾 Add Synchronization
* 📡 Implement async I/O (`select` / `epoll`)
* 📊 Add performance benchmarking (ops/sec)
* 🔐 Improve fine-grained locking for better concurrency
* 🌐 Add HTTP interface

---