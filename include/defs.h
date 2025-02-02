#pragma once

#define __REV__ "0.0.1"

struct buf;
struct context;
struct file;
struct inode;
struct pipe;
struct proc;
struct rtcdate;
struct spinlock;
struct sleeplock;
struct stat;
struct superblock;
struct trapframe;
struct pci_func;
struct netdev;
struct netcard_opts;
struct socket;
struct sockaddr;
struct hostent;
struct netdb_answer;
struct in_addr;

// bio.c
void binit(void);
struct buf *bread(uint, uint);
void brelse(struct buf *);
void bwrite(struct buf *);

// console.c
void consoleinit(void);
void cprintf(char *, ...);
void cputc(int);
void consoleintr(int(*)(void));

// debug.c
void panic(char *) __attribute__((noreturn));

// date.c
uint32 unixime_in_seconds(const struct rtcdate *date);

// exec.c
int exec(char *, char **);

// file.c
struct file *filealloc(void);
void fileclose(struct file *);
struct file *filedup(struct file *);
void fileinit(void);
int fileread(struct file *, char *, int n);
int filestat(struct file *, struct stat *);
int filewrite(struct file *, char *, int n);

// fs.c
void readsb(int dev, struct superblock *sb);
int dirlink(struct inode *, char *, uint);
struct inode *dirlookup(struct inode *, char *, uint *);
struct inode *ialloc(uint, short);
struct inode *idup(struct inode *);
void iinit(int dev);
void ilock(struct inode *);
void iput(struct inode *);
void iunlock(struct inode *);
void iunlockput(struct inode *);
void iupdate(struct inode *);
int namecmp(const char *, const char *);
struct inode *namei(char *);
struct inode *nameiparent(char *, char *);
int readi(struct inode *, char *, uint, uint);
void stati(struct inode *, struct stat *);
int writei(struct inode *, char *, uint, uint);

// ide.c
void ideinit(void);
void ideintr(void);
void iderw(struct buf *);

// ioapic.c
void ioapicenable(int irq, int cpu);
extern uchar ioapicid;
void ioapicinit(void);

// page_alloc.c
char *page_alloc(void);
void page_free(char *);
void kinit1(void *, void *);
void kinit2(void *, void *);

// kbd.c
void kbdintr(void);

// lapic.c
void cmostime(struct rtcdate *r);
int lapicid(void);
extern volatile uint *lapic;
void lapiceoi(void);
void lapicinit(void);
void lapicstartap(uchar, uint);
void microdelay(int);

// log.c
void initlog(int dev);
void log_write(struct buf *);
void begin_op();
void end_op();

// mp.c
extern int ismp;
void mpinit(void);

// picirq.c
void picenable(int);
void picinit(void);

// pipe.c
int pipealloc(struct file **, struct file **);
void pipeclose(struct pipe *, int);
int piperead(struct pipe *, char *, int);
int pipewrite(struct pipe *, char *, int);

//PAGEBREAK: 16
// proc.c
int cpuid(void);
void exit(int);
int fork(void);
int growproc(int);
int killproc(int);
struct cpu *mycpu(void);
struct proc *myproc();
void pinit(void);
void procdump(void);
void scheduler(void) __attribute__((noreturn));
void sched(void);
void setproc(struct proc *);
void sleep(void *, struct spinlock *);
void userinit(void);
int wait(int *);
int waitpid(int, int *);
void wakeup(void *);
void yield(void);
sighandler_t signal(int signal, sighandler_t handler);
int signal_deliver(int pid, int signal);
void signal_return();
void run_signal(struct trapframe *);

// sysproc.c
void seterror(int);

// swtch.S
void swtch(struct context **, struct context *);

// spinlock.c
void acquire(struct spinlock *);
void getcallerpcs(void *, uint *);
int holding(struct spinlock *);
void assert_holding(struct spinlock *);
void initlock(struct spinlock *, char *);
void release(struct spinlock *);
void pushcli(void);
void popcli(void);

// sleeplock.c
void acquiresleep(struct sleeplock *);
void releasesleep(struct sleeplock *);
int holdingsleep(struct sleeplock *);
void initsleeplock(struct sleeplock *, char *);

// string.c
int memcmp(const void *, const void *, uint);
void *memmove(void *, const void *, uint);
void *memset(void *, int, uint);
char *safestrcpy(char *, const char *, int);
int strlen(const char *);
int strnlen(const char *, int);
int strncmp(const char *, const char *, uint);
char *strncpy(char *, const char *, int);

// syscall.c
int argint(int, int *);
int argptr(int, char **, int);
int argstr(int, char **);
int fetchint(uint, int *);
int fetchstr(uint, char **);
void syscall(void);

// sysfile.c
int argfd(int, int *, struct file **);
int fdalloc(struct file *);

// timer.c
void timerinit(void);

// trap.c
void idtinit(void);
extern uint ticks;
void tvinit(void);
extern struct spinlock tickslock;

// uart.c
void uartinit(void);
void uartintr(void);
void uartputc(int);

// vm.c
void seginit(void);
void kvmalloc(void);
pde_t *setupkvm(void);
char *uva2ka(pde_t *, char *);
int allocuvm(pde_t *, uint, uint);
int deallocuvm(pde_t *, uint, uint);
void freevm(pde_t *);
void inituvm(pde_t *, char *, uint);
int loaduvm(pde_t *, char *, struct inode *, uint, uint);
pde_t *copyuvm(pde_t *, uint);
void switchuvm(struct proc *);
void switchkvm(void);
int copyout(pde_t *, uint, void *, uint);
void clearpteu(pde_t *pgdir, char *uva);
int mappages(pde_t *pgdir, void *va, uint size, uint pa, int perm);
int remappages(pde_t *pgdir, void *va, uint size, uint pa, int perm);

// number of elements in fixed-size array
#define NELEM(x) (sizeof(x)/sizeof((x)[0]))

// offset of a struct member
#define offsetof(type, member)  __builtin_offsetof (type, member)

// get struct pointer from member
#define container_of(ptr, type, member) ({                      \
        const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
        (type *)( (char *)__mptr - offsetof(type,member) );})

#define LIST_POISON1 0xbad0
#define LIST_POISON2 0xbad1

// pci.c

void pci_init(void);
void pci_func_enable(struct pci_func *f);

// net.c
void netinit(void);
void netstart(void);
int nettimer(void);
struct netdev *nic_register(char *name, struct pci_func *pcif, struct netcard_opts *opts, void *prvt);
struct netdev *nic_unregister(struct netdev *nic);
void nic_free(struct netdev *nic);
struct netdev *find_card_by_id(int n);
struct netdev *find_card_by_name(char *name);
void netbegin_op();
void netend_op();

// netdb.c
void netdbinit(void);
struct netdb_answer *netdb_query(char *name, int type);
void netdb_free(struct netdb_answer *);
void netdb_dump_answer(struct netdb_answer *);

// netutils.c
char *inet_ntoa(struct in_addr in);
int inet_aton(const char *cp, struct in_addr *ap);

// virtio_nic.c
int virtio_nic_attach(struct pci_func *pcif);

// e1000_nic.c
void e1000_init(void);
int e1000_nic_attach(struct pci_func *pcif);

// socket.c
void socketinit(void);
struct file *socketalloc(int domain, int type, int protocol, int *err);
void socketclose(struct socket *);
int socketconnect(struct socket *, struct sockaddr *, int);
int socketbind(struct socket *, struct sockaddr *, int);
int socketlisten(struct socket *, int);
struct file *socketaccept(struct socket *skt, struct sockaddr *addr, int *addrlen, int *err);
int socketrecv(struct socket *skt, char *buf, int len, int flags);
int socketsend(struct socket *skt, char *buf, int len, int flags);
int socketioctl(struct socket *, int, void *);
int socketsendto(struct socket *skt, char *buf, int len, int flags, struct sockaddr *addr, int addrlen);
int socketrecvfrom(struct socket *skt, char *buf, int len, int flags, struct sockaddr *addr, int *addrlen);
int socketgetsockopt(struct socket *skt, int level, int optname, void *optval, int *optlen);
int socksetsockopt(struct socket *skt, int level, int optname, void *optval, int optlen);

// pmm.c
void pmminit(void);

// printfmt.c
int snprintf(char *buf, int n, const char *fmt, ...);
#define sprintf(buf, fmt, ...) snprintf(buf, 256, fmt, __VA_ARGS__);
void printfmt(void (*putch)(int, void *), void *putdat, const char *fmt, ...);
