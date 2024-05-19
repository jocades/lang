from sys import argv
import json


def main():
    n1 = int(argv[1])
    n2 = int(argv[2])

    print(f'sum: {n1 + n2}')


def object():
    print(argv[1])
    parsed = json.loads(argv[1])
    print(parsed)

    print(parsed['name'])


if __name__ == "__main__":
    object()
