import numpy as np
import random
import sys

def get_random_letter(letter):
    a = ['A', 'C', 'T', 'G']
    a.remove(letter)
    return random.choice(a)

def no_error(file, generated_number):
    with open(file) as s:
        total = 0
        unique = []
        while (total < generated_number):
            current_sequence = ""
            rand_number = random.randint(0, 10000)
            s.seek(rand_number)

            for i in range(0, 16):
                char = s.read(1)
                if char == '\n':
                    char = s.read(1)
                current_sequence += char

            unique.append(current_sequence)
            total += 1
        unique_frags = set(unique)
    # print("Number of Unique Fragments: ", len(unique_frags))
    return unique

def with_error(file, frag_array, p_error = 0.05):
    total = 0
    unique = []

    avg_num_of_failuress = int(np.random.geometric(p=p_error, size=100).sum() / 100)

    index = int(avg_num_of_failuress / 16)
    string_position = int(avg_num_of_failuress % 16)

    while (total < len(frag_array)):

        x = list(frag_array[total])

        x[string_position] = get_random_letter(x[string_position])

        x = "".join(x)

        frag_array[total] = x

        total += index

    unique_frags = set(frag_array)
    # print("Number of Unique Fragments: ", len(unique_frags))
    return len(unique_frags)



if __name__ == '__main__':
    if sys.argv[1] == "1A":
        avg_num_of_failuress = np.random.geometric(p=0.005, size=100)
        print("Failures: {}".format(int(avg_num_of_failuress.sum() / 100)))

    elif sys.argv[1] == "1B":
        avg_num_of_succeses = np.random.binomial(10000, p=0.005)
        print("Succeses: {}".format(int(avg_num_of_succeses)))

    elif sys.argv[1] == "2A":
        total_unique = 0
        for i in range(0, 100):
            frags, unique_frags = no_error(str(sys.argv[2]), 100000)
            total_unique += len(unique_frags)
        print("Avg. Number of Unique Fragments (100 trials): {}".format(int(total_unique/100)))

    elif sys.argv[1] == "2B":
        total_unique = 0
        frags, unique_frags = no_error(str(sys.argv[2]), 100000)
        for i in range(0, 100):
            unq_frags = with_error(sys.argv[2], frags, p_error=0.01)
            total_unique += unq_frags
        print("Avg. Number of Unique Fragments (100 trials): {}".format(int(total_unique/100)))

    elif sys.argv[1] == "2C":
        total_unique = 0
        frags, unique_frags = no_error(str(sys.argv[2]), 100000)
        for i in range(0, 60):
            unq_frags = with_error(sys.argv[2], frags, p_error=0.05)
            total_unique += unq_frags
            print("Iteration: {} Unique Fragments: {}".format(i, int(total_unique)))

        print("Avg. Number of Unique Fragments (100 trials): {}".format(int(total_unique/100)))
