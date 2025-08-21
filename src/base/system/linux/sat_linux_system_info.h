


//------------------------------
// libc version
//------------------------------

// ldd --version

/*
    libc version:

    #include <stdio.h>
    #include <gnu/libc-version.h>
    int main (void)
    {
        puts (gnu_get_libc_version());
        return 0;
    }
*/

//------------------------------
// cpu info
//------------------------------

/*
    #define _GNU_SOURCE
    #include <stdio.h>
    #include <stdlib.h>
    int main(int argc, char **argv)
    {
        FILE *cpuinfo = fopen("/proc/cpuinfo", "rb");
        char *arg = 0;
        size_t size = 0;
        while(getdelim(&arg, &size, 0, cpuinfo) != -1)
        {
            puts(arg);
        }
        free(arg);
        fclose(cpuinfo);
        return 0;
    }

*/

// num_cpus = sysconf( _SC_NPROCESSORS_ONLN );    

/*
    #include <stdio.h>
    #include <libcpuid.h>
    int main(void)
    {
        if (!cpuid_present()) {
            printf("Sorry, your CPU doesn't support CPUID!\n");
            return -1;
        }
        struct cpu_raw_data_t raw;
        struct cpu_id_t data;
        if (cpuid_get_raw_data(&raw) < 0)
        {
            printf("Sorry, cannot get the CPUID raw data.\n");
            printf("Error: %s\n", cpuid_error());
            return -2;
        }
        if (cpu_identify(&raw, &data) < 0)
        {
            printf("Sorrry, CPU identification failed.\n");
            printf("Error: %s\n", cpuid_error());
            return -3;
        }
        printf("Processor has %d physical cores\n", data.num_cores);
        return 0;
    }
*/

//------------------------------
// kernel
//------------------------------

/*
    #include <stdio.h>
    #include <stdlib.h>
    #include <errno.h>
    #include <ctype.h>
    #include <sys/utsname.h>
    int main(void)
    {
        struct utsname buffer;
        char *p;
        long ver[16];
        int i=0;
        errno = 0;
        if (uname(&buffer) != 0)
        {
            perror("uname");
            exit(EXIT_FAILURE);
        }
        printf("system name = %s\n", buffer.sysname);
        printf("node name   = %s\n", buffer.nodename);
        printf("release     = %s\n", buffer.release);
        printf("version     = %s\n", buffer.version);
        printf("machine     = %s\n", buffer.machine);
        #ifdef _GNU_SOURCE
            printf("domain name = %s\n", buffer.domainname);
        #endif
        p = buffer.release;
        while (*p)
        {
            if (isdigit(*p))
            {
                ver[i] = strtol(p, &p, 10);
                i++;
            } else
            {
                p++;
            }
        }
        printf("Kernel %d Major %d Minor %d Patch %d\n", ver[0], ver[1], ver[2], ver[3]);
        return EXIT_SUCCESS;
    }
*/

/*
    struct utsname
    {
        char sysname[];         // Operating system name (e.g., "Linux")
        char nodename[];        // Name within "some implementation-defined network"
        char release[];         // Operating system release (e.g., "2.6.28")
        char version[];         // Operating system version
        char machine[];         // Hardware identifier
        #ifdef _GNU_SOURCE
            char domainname[];  // NIS or YP domain name
        #endif
    }

    #include <sys/utsname.h>
    int uname(struct utsname *buf);
*/

//------------------------------
// desktop
//------------------------------

/*
    #include <cstdlib>
    #include <iostream>
    int main()
    {
        const char* const XDG_CURRENT_DESKTOP   = std::getenv("XDG_CURRENT_DESKTOP");
        const char* const GDMSESSION            = std::getenv("GDMSESSION");
        std::cout << "XDG_CURRENT_DESKTOP=\""   << ((nullptr != XDG_CURRENT_DESKTOP) ? XDG_CURRENT_DESKTOP : "<none>") << "\"\n";
        std::cout << "GDMSESSION=\""            << ((nullptr != GDMSESSION)          ? GDMSESSION :          "<none>") << "\"\n";
        return 0;
    }
*/
