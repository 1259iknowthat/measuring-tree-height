#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
#include <random>
#include <chrono>

// Random Elements
void gen_random_array(FILE *f){
    std::vector<int> random_elements;
    for(int i = 0; i < 10e5; i++)       
        random_elements.push_back(i);
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(random_elements.begin(), random_elements.end(), std::default_random_engine(seed));
    for (int i: random_elements){
        fprintf(f, "%d ", i);
    }
    fputc('\n',f);
}

int main(){
    FILE *f;
    f = fopen("input-data.txt", "w");
    puts("[+] Generating tests ....");
    for (int i = 0; i < 10; i++)
        gen_random_array(f);
    fclose(f);
    puts("[+] Done!");
}