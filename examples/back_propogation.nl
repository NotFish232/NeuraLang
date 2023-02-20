# define neural network constraints
setActivationFunction(leakyRelU)
setOutputFunction(softMax)
setNumberOfHiddenLayers(3)
setLayerDim(10)

let trainingData = """DATA HERE"""

def train(i32 epochs = 50) -> void {
    i32 i = 0;
    # train neural network on trainingData for n epochs
    while (i < epochs) {
        predict(trainingData, true)
        i++
    }
}

train()

while (true) {
    # ask user for input and predict data using neural network
    string inp = input("Enter a data value to predict: ")
    print(predict(inp, false))
}