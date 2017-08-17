#include <iostream>
#include <vector>

struct task
{
    int time_in;
    int num_servers;
    int duration;

    task(int t, int k, int d) : time_in(t), num_servers(k), duration(d) { }
};

int main()
{
    int num_servers, num_tasks;

    std::cin >> num_servers >> num_tasks;

    std::vector<task> tasks;

    for(int i = 0; i < num_tasks; i++) {
        int t, k, d;

        std::cin >> t >> k >> d;

        tasks.push_back(task(t, k, d));
    }

    std::sort(tasks.begin(), tasks.end(), [](task& a, task& b) {
        return a.time_in < b.time_in;
    });

    std::vector<int> time_free((size_t)num_servers, -1);

    for(task& current_task : tasks) {
        int current_time = current_task.time_in;

        long servers_free = std::count_if(time_free.begin(), time_free.end(), [current_time](int t) {
            return t <= current_time;
        });

        if(servers_free < current_task.num_servers) {
            std::cout << -1 << std::endl;

            continue;
        }

        int sum_of_indices = 0;
        int occupied_servers = 0;

        for(int i = 0; occupied_servers < current_task.num_servers; i++) {
            if(time_free[i] <= current_time) {
                time_free[i] = current_time + current_task.duration;

                sum_of_indices += i + 1;

                occupied_servers += 1;
            }
        }

        std::cout << sum_of_indices << std::endl;
    }
}
