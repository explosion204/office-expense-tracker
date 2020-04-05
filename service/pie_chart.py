import matplotlib.pyplot as plt

def pie_plot(items: dict):
    labels = list(items.keys())
    sizes = list(items.values())
    patches, texts = plt.pie(sizes, startangle=90)
    plt.legend(patches, labels, loc="best")
    plt.axis('equal')
    plt.tight_layout()
    plt.savefig('plot.png')

test_dict = {'a': 1, 'b': 1}
pie_plot(test_dict)