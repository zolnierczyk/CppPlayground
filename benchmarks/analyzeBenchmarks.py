# This Python file uses the following encoding: utf-8
import matplotlib.pyplot as plt
import json

def makePlotIterationBasic(benchmakrAsJson):
    benchmarkArray = benchmakrAsJson["benchmarks"];
    nameOfBenchmarkBaseIter = "IterateAndMultiplayOverLargArrayWithStep"
    nameOfBenchmarkReverseIter = "IterateReverseAndMultiplayOverLargArrayWithStep"
    stepsForBaseIter = []
    timesForBaseIter = []
    stepsForReverseIter = []
    timesForReverseIter = []
    for elem in benchmarkArray:
        nameArray = elem["name"].split("/")
        paramValue = int(elem["name"].split("/")[-1])
        if (nameArray[-2] == nameOfBenchmarkBaseIter):
            stepsForBaseIter.append(paramValue)
            timesForBaseIter.append(elem["cpu_time"])
        if (nameArray[-2] == nameOfBenchmarkReverseIter):
            stepsForReverseIter.append(paramValue)
            timesForReverseIter.append(elem["cpu_time"])

    timeTheory = [ float(timesForBaseIter[0]) / stepsForBaseIter[i] for i in range(0, len(stepsForBaseIter))]

    plt.clf()
    plt.plot(stepsForBaseIter, timesForBaseIter, label="Forward Iter")
    plt.plot(stepsForReverseIter, timesForReverseIter, label="Reverse Iter")
    plt.plot(stepsForBaseIter, timeTheory, label="Theoretical Iter")
    plt.ylabel('Time in ns')
    plt.xlabel('Steps size')
    plt.legend()
    plt.grid()
    plt.title("Computer: " + benchmakrAsJson["context"]["host_name"])
    plt.savefig("BasicIteration" + benchmakrAsJson["context"]["host_name"] + ".png")

def makePlotIterationRandom(benchmakrAsJson):
    benchmarkArray = benchmakrAsJson["benchmarks"];
    nameOfBenchmarkLoopupIter = "IterateWihtLookupAndMultiplayOverLargArrayWithStep"
    nameOfBenchmarkLoopupRandomIter = "IterateWihtLookupRandomAndMultiplayOverLargArrayWithStep"
    stepsForBaseIter = []
    timesForBaseIter = []
    stepsForRandomIter = []
    timesForRandomIter = []
    for elem in benchmarkArray:
        nameArray = elem["name"].split("/")
        paramValue = int(elem["name"].split("/")[-1])
        if (nameArray[-2] == nameOfBenchmarkLoopupIter):
            stepsForBaseIter.append(paramValue)
            timesForBaseIter.append(elem["cpu_time"])
        if (nameArray[-2] == nameOfBenchmarkLoopupRandomIter):
            stepsForRandomIter.append(paramValue)
            timesForRandomIter.append(elem["cpu_time"])

    plt.clf()
    plt.plot(stepsForBaseIter, timesForBaseIter, label="Forward Iter")
    plt.plot(stepsForRandomIter, timesForRandomIter, label="Random Iter")
    plt.ylabel('Time in ns')
    plt.xlabel('Steps size')
    plt.legend()
    plt.grid()
    plt.title("Computer: " + benchmakrAsJson["context"]["host_name"])
    plt.savefig("RandomIteration" + benchmakrAsJson["context"]["host_name"] + ".png")

if __name__ == "__main__":
    benchmarkFile = open("sample.json", "r")
    benchmakrString = benchmarkFile.read()
    benchmakrAsJson = json.loads(benchmakrString)
    makePlotIterationBasic(benchmakrAsJson)
    makePlotIterationRandom(benchmakrAsJson)

