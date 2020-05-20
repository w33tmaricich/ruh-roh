#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/kthread.h>

#include <linux/errno.h>
#include <linux/types.h>

#include <linux/netdevice.h>
#include <linux/ip.h>
#include <linux/in.h>

// #include <linux/smp_lock.h>
#include <linux/delay.h>
#include <linux/un.h>
#include <linux/unistd.h>
#include <linux/wait.h>
#include <linux/ctype.h>
#include <asm/unistd.h>
#include <net/sock.h>
#include <net/tcp.h>
#include <net/inet_connection_sock.h>
#include <net/request_sock.h>

#define MODULE_NAME "ruh-roh"

struct ruhroh_service {
    int running;
    struct socket *listen_socket;
    struct task_struct *thread;
    struct task_struct *accept_worker;
};

struct ruhroh_service *ruhroh_svc;

int ruhroh_shutdown(void) {
    return 1;
}

int ruhroh_recev(struct socket *sock, unsigned char *buf, int len) {
    return 1;
}

int ruhroh_accept_worker(void) {
    return 1;
}

int ruhroh_start_listen(void) {
    printk(KERN_INFO MODULE_NAME": start_listen\n");
    return 1;
}

int ruhroh_start(void) {
    ruhroh_svc->running = 1;

    ruhroh_svc->thread = kthread_run((void *)ruhroh_start_listen, NULL, MODULE_NAME);

    return 1;
}

int init_module(void) {
    printk(KERN_INFO MODULE_NAME": module init\n");
    ruhroh_svc = kmalloc(sizeof(struct ruhroh_service), GFP_KERNEL);
    ruhroh_start();
    printk(KERN_INFO MODULE_NAME": initialized\n");
    return 0;
}

void cleanup_module(void) {
    int err;

    printk(KERN_INFO "ruh-roh cleanup\n");
    if(ruhroh_svc->thread == NULL)
        printk(KERN_INFO MODULE_NAME": no kernel thread to kill\n");
    else {
        err = kthread_stop(ruhroh_svc->thread);
        // err = kthread_stop(ruhroh_svc->accept_worker);
    }

    kfree(ruhroh_svc);
    ruhroh_svc = NULL;

    printk(KERN_INFO MODULE_NAME": module unloaded\n");
}
