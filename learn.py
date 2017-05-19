import pandas as pd
import numpy as np
import numpy.random

from sklearn.ensemble import AdaBoostClassifier
from sklearn.model_selection import train_test_split

data = pd.read_csv("dataset.csv", sep=";")
data = data.drop(data.columns[[0, 1, 2, 3]], axis=1)

df = data.as_matrix()

X = df[:, :df.shape[1] - 1]
y = df[:, df.shape[1] - 1:].reshape(df.shape[0])

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

bdt = AdaBoostClassifier(n_estimators=17)

bdt.fit(X_train, y_train)

out = bdt.predict(X_train)
print("Nb train: " + str(y_train.shape[0]))
print((out == y_train).sum() / y_train.shape[0])

print("Nb test: " + str(y_test.shape[0]))
out = bdt.predict(X_test)
print((out == y_test).sum() / y_test.shape[0])
