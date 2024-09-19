# NeuralNetworks
A work in progress implementation of a feed forward neural network in C++ without the use of external libraries. The class NeuralNetwork is designed to take in the parameters:
  - learning rate
  - the activation functions for each layer
  - the number of layers and the number of hidden nodes for each layer
  - batch size
  
The constructor initializes each layer automatically. The class then provides a function for feeding data forward and one for training the neural network. 

The current working activations functions are:
  - sigmoid 
  - ReLU
  - tanh
  - softsign
  
 The class DataConverter parses a csv file which contains a dataset of pixel values with colour values ranging from 0 to 255 (designed for the MNIST dataset).
 The format of the csv file must be:
  - each line represents one data point (one picture of a handwritten digit)
  - the first value in each line represents the label
  - every other value represents a pixel value
  - all values are comma seperated
  
DataConverter parses these files, normalizes the colour values to be between 0 and 1 and stores them in public vectors of matrices, which then can easily be fed into the neural network. The class needs the parameters
  - path of the csv file
  - the number of data points in the data set
  - the dimension of the input vectors which are to be fed into the network
  - the dimension of the output vector for constructing the label vectors to be easily comparable with the output of the network
  - the batch size in order to combine input vectors and label vectors into batches (matrices with the number of columns equal to the batch size)
  
The matrix class for arithmetic datatypes implements the algebraic functions for the neural network. It is designed for minimizing unnecessary copies and using move assignments and constructors instead.