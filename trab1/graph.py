import matplotlib.pyplot as plt
import csv
import sys

def get_title(archive_name):
    return [value.lower().replace('.csv', '') for value in archive_name.split('/')]

def read_csv(archive_name: str) -> tuple:
    x = []
    y = []
    with open(archive_name, 'r') as csv_file:
        dataset = csv.reader(csv_file, delimiter=';')
        next(dataset)
        for line in dataset:
            number, runtime = line
            x.append(int(number.strip()))
            y.append(float(runtime.strip()))

    return x, y, get_title(archive_name)[-1]

def plot_scatter(data: list, save_path: str) -> None:
    legend = []
    plt.ylabel("Runtime (s)")
    plt.xlabel("Tamanho N")

    splitted_path = get_title(save_path)
    language = splitted_path[len(splitted_path)-2].upper()
    plt.title(f"Gráfico para linguagem {language}")

    for x, y, archive_name in data:
        plt.plot(x, y)
        legend.append(archive_name)

    plt.legend(legend)
    plt.savefig(save_path)
    print(f"Graph generated for the language: {language}")

if __name__ == "__main__":
    try:
        if(len(sys.argv) != 4):
            print('Could not save the file. Check your arguments')
            exit()
    except:
        print('Could not save the file. Check your arguments')
        exit()

    data = []
    for path in sys.argv[2:]:
        data.append(read_csv(path))

    plot_scatter(data, sys.argv[1])