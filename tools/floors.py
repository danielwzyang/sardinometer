import matplotlib.pyplot as plt

log = "measurements/112326_service.log"
flat_compare = 5 # which neighbor +/- n samples away to compare to
flat_width = 15 # how many flat readings constitute a floor
error_margin = 0.2

alt = []
for line in open(log):
    if line.startswith("altitude"):
        alt.append(float(line.split()[2]))

floors = []
for i in range(len(alt) - flat_compare):
    if abs(alt[i + flat_compare] - alt[i]) < error_margin:
        if floors and abs(alt[i] - floors[-1][-1]) < 1:
            floors[-1].append(alt[i])
        else:
            floors.append([alt[i]])

floors = [sum(f) / len(f) for f in floors if len(f) > flat_width]
zero = floors[0]
floors = [f - zero for f in floors]
alt = [a - zero for a in alt]

# LL1 missing in this sample
print("{" + ", ".join(f"{f:.2f}" for f in floors) + "}")
names = ["LL2", "G", "2", "3", "4", "5", "6", "7", "8", "9", "10"]
for name, f in zip(names, floors):
    print(name, round(f, 2))
    plt.axhline(f, color="pink")
    plt.text(0, f, name)

plt.plot(alt)
plt.show()
