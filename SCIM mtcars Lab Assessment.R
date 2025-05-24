library(dplyr)
library("corrplot")
library(caTools)
library(ggplot2)




data(mtcars)

print(head(mtcars))


#Check for Null Values
sum(is.na(mtcars))

summary(mtcars)

# cyl, vs, am, gear and carb seem to be discrete and categorical
# ie not continuous

print("Summary Statistics of mtcars mpg:")
summary(mtcars$mpg)

print("Summary Statistics of mtcars display:")
summary(mtcars$disp)

print("Summary Statistics of mtcars hp:")
summary(mtcars$hp)

print("Summary Statistics of mtcars drat:")
summary(mtcars$drat)

print("Summary Statistics of mtcars wt:")
summary(mtcars$wt)

print("Summary Statistics of mtcars qsec:")
summary(mtcars$qsec)


#select all rows with 6 cylinders

sixcyl = mtcars[mtcars$cyl == 6, ]

#select all rows with 4 cylinders

fourcyl = mtcars[mtcars$cyl == 4, ]


print(sixcyl)
print(fourcyl)


#Mean, standard deviation and number of mpgs in each cylinder number

#Mean

mean(sixcyl$mpg)
mean(fourcyl$mpg)

#Standard Deviation
sd(sixcyl$mpg)
sd(fourcyl$mpg)

#Number of entries where transmission is zero
sum(mtcars$am == 0)


#The T Test
t.test(sixcyl$mpg, fourcyl$mpg)


#One Sample Proportion Test
prop.test(19,32,p=0.5,alternative = "two.sided")


#Get Numerical Columns 
cormtcars <- subset(mtcars, select = -c(2,8,9,10,11))
print(cormtcars)


cor_data = cor(cormtcars)
print(cor_data)

corrplot(cor_data, method = "color")
corrplot(cor_data, method = "circle")
corrplot(cor_data, method = "number")

#To get an idea of what direction the line should take
correlation_mpg_wt <- cor.test(mtcars$wt, mtcars$mpg)
print(correlation_mpg_wt)



#Simple Linear Regression

split = sample.split(mtcars$mpg, SplitRatio = 0.7)
trainingset = subset(mtcars, split == TRUE)
testset = subset(mtcars, split == FALSE)


lm.sr= lm(formula = mpg ~ wt,
          data = trainingset)
#Summary of the model
summary(lm.sr)


#Multiple Linear Regression

set.seed(42)
split = sample.split(mtcars$mpg, SplitRatio=0.8)
training_set = subset(mtcars, split == TRUE)
test_set = subset(mtcars, split == FALSE)

# Fitting Multiple Linear Regression to the Training set
m.regressor = lm(formula = mpg ~ wt + hp + cyl,
                 data = training_set)

# Predicting the Test set results

#Summary of the model

y_pred = predict(m.regressor, newdata = test_set)

summary(m.regressor)
print(y_pred)



#The Scatter Plot

attach(mtcars)
plot(wt, mpg, main = "Scatterplot of Weight vs Miles Per Gallon", xlab = "Car Weight", ylab = "Miles Per Gallon", pch = 18)

#Overlay with the Linear Regression Line

abline(lm.sr,col='darkgreen') 





# The Boxplot


boxplot(mpg ~ cyl, data = mtcars, col = "orange",
        main = "Miles Per Gallon given Cylinders",
        xlab = "Cylinder Count",
        ylab = "Miles Per Gallon" )



#The Histogram

mpg = mtcars$mpg

ggplot(data = mtcars, aes(x = mpg))+ 
  geom_histogram(aes(y = after_stat(density)), binwidth = 5, color = "orange", fill = "white") + 
  labs(title = "MPG Histogram", x = "MPG Value", y = "Frequency") + geom_density(col = "green")  + stat_function(fun = dnorm, col = "red", lwd = 1)

