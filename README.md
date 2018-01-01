# LDACAFFE
The current repository contains the LDA part of the project.
For a better organized repository, please check
https://github.com/cocosci/LDA_JAVA.
##How to execute?

<ul>
<li>Navigate down to the LDACAFFE home directory.</li>
<li>Type "make".</li>
<li>Then type ./final 100 "toyinput.dat" 4 10 0.1 5 "file"</li>
<li>By the way, it means ./final numiteration inputdata numtopic alpha beta numwordspertopic typeofinput</li>
<li>It supports two types of input. The toy one contains all the docs in a single file. Each doc is just a line which can be quite long though. The second one contains all docs in a folder, each doc is a single file. To try the second case, you may want to type ./final 1000 "/nips12/" 10 0.5 0.1 5 "dir"</li>
<li>By the way, it means ./final numiteration inputdata numtopic alpha beta numwordspertopic typeofinput</li>
</ul>

##How to check the result?
Results are in theta.txt(distribution of topics for docs), top k words per topic.txt(distribution of words for topics)


----------------------------------------------------------------------------------------------------
Result in running all nips papers from 2012

Topic 0:
learning
algorithm
generalization
training
examples

Topic 1:

In
model
A
data

Topic 2:
neurons
neuron
synaptic
input
visual

Topic 3:
frequency
sound
state
system
cue

Topic 4:
Markov
language
Bayesian
sequence
sampling

Topic 5:
nodes
networks
network
node
variational

Topic 6:
image
images
feature
features
mutual

Topic 7:
state
policy
belief
states
function

Topic 8:
sources
source
data
nonlinear
blind

Topic 9:
kernel
set
SVM

solution

The command to run LDA for that result: ./final 1000 "/nips12/" 10 0.5 0.1 5 "dir"
--------------------------------------------------------------------------------------------------------------
The result for my toy example that really accompanies me for this month. Thank you toyinput.dat!

Topic 0:
Beijing
protests
party
power

Topic 1:
learning
concepts
object
human

Topic 2:
man
1989
Tiananmen
tank

Topic 3:
Bayesian
models
cognitive
intuitive



How to run and get the above result? ./final 2000 "toyinput.dat" 4 0.5 0.1 4 "di"
And then, sublime top\ k\ words\ per\ topic.txt

0.003106 0.208075 0.003106 0.785714 

0.009804 0.166667 0.009804 0.813725 

0.015152 0.954545 0.015152 0.015152 

0.833333 0.038462 0.115385 0.012821 

0.011905 0.011905 0.940476 0.035714 

0.006329 0.905063 0.069620 0.018987 

0.065476 0.017857 0.910714 0.005952 

0.524510 0.044118 0.426471 0.004902 

0.801587 0.007937 0.150794 0.039683 
 
doc1
 
My colleagues and I in the Computational Cognitive Science group study one of the most basic and distinctively human aspects of cognition: the ability to learn so much about the world, rapidly and flexibly. Given just a few relevant experiences, even young children can infer the meaning of a new word, the hidden properties of an object or substance, or the existence of a new causal relation or social rule.These inferences go far beyond the data given: after seeing three or four examples of "horses", a two-year-old will confidently judge whether any new entity is a horse or not, and she will be mostly correct, except for the occasional donkey or camel. We want to understand these everyday inductive leaps in computational terms. What is the underlying logic that supports reliable generalization from so little data? What are its cognitive and neural mechanisms, and how can we build more powerful learning machines based on the same principles? These questions demand a multidisciplinary approach. Our group's research combines computational models (drawing chiefly on Bayesian statistics, probabilistic generative models, and probabilistic programming) with behavioral experiments in adults and children. Our models make strong quantitative predictions about behavior, but more importantly, they attempt to explain why cognition works, by viewing it as an approximation to ideal statistical inference given the structure of natural tasks and environments. Current research in our group explores the computational basis of many aspects of human cognition: learning concepts, judging similarity, inferring causal connections, forming perceptual representations, learning word meanings and syntactic principles in natural language, noticing coincidences and predicting the future, inferring the mental states of other people, and constructing intuitive theories of core domains, such as intuitive physics, psychology, biology, or social structure.
 
doc2
 
We present an introduction to Bayesian inference as it is used in probabilistic models of cognitive development. Our goal is to provide an intuitive and accessible guide to the what, the how, and the why of the Bayesian approach: what sorts of problems and data the framework is most relevant for, and how and why it may be useful for developmentalists. We emphasize a qualitative understanding of Bayesian inference, but also include information about additional resources for those interested in the cognitive science applications, mathematical foundations, or machine learning details in more depth. In addition, we discuss some important interpretation issues that often arise when evaluating Bayesian models in cognitive science.

doc3

One-shot learning is an object categorization problem of current research interest in computer vision. Whereas most machine learning based object categorization algorithms require training on hundreds or thousands of images and very large datasets, one-shot learning aims to learn information about object categories from one, or only a few, training images.

doc4

Jiang Zemin came to power unexpectedly as a 'compromise candidate' following the Tiananmen Square protests of 1989, when he replaced Zhao Ziyang as General Secretary after Zhao was ousted for his support for the student movement. With the waning influence of Eight Elders due to old age and with the death of Deng Xiaoping, Jiang consolidated his hold on power and became the "paramount leader" of the country in the 1990s.

doc5

A man who stood in front of a column of tanks on June 5, 1989, the morning after the Chinese military had suppressed the Tiananmen Square protests of 1989 by force, became known as the Tank Man, Unknown Protester or Unknown Rebel. As the lead tank maneuvered to pass by the man, he repeatedly shifted his position in order to obstruct the tank's attempted path around him. The incident was filmed and seen worldwide.

doc6

People learning new concepts can often generalize successfully from just a single example, yet machine learning algorithms typically require tens or hundreds of examples to perform with similar accuracy. People can also use learned concepts in richer ways than conventional algorithms—for action, imagination, and explanation. We present a computational model that captures these human learning abilities for a large class of simple visual concepts: handwritten characters from the world’s alphabets. The model represents concepts as simple programs that best explain observed examples under a Bayesian criterion. On a challenging one-shot classification task, the model achieves human-level performance while outperforming recent deep learning approaches. We also present several “visual Turing tests” probing the model’s creative generalization abilities, which in many cases are indistinguishable from human behavior.

doc7

The incident took place near Tiananmen on Chang'an Avenue, which runs east-west along the north end of Tiananmen Square in Beijing, China, on June 5, 1989, one day after the Chinese government's violent crackdown on the Tiananmen protests.[4] The man stood in the middle of the wide avenue, directly in the path of a column of approaching Type 59 tanks. He wore a white shirt and black trousers, and he held a shopping bag.[5] As the tanks came to a stop, the man gestured towards the tanks with his bag. In response, the lead tank attempted to drive around the man, but the man repeatedly stepped into the path of the tank in a show of nonviolent action.[6] After repeatedly attempting to go around rather than crush the man, the lead tank stopped its engines, and the armored vehicles behind it seemed to follow suit. There was a short pause with the man and the tanks having reached a quiet, still impasse.

doc8

During the 1989 student demonstrations in Beijing, the Chinese People's Liberation Army (PLA) played a decisive role in enforcing martial law, suppressing the demonstrations by force and upholding the authority of the Chinese Communist Party. The scale of the military's mobilization for a domestic event and degree of bloodshed inflicted against civilians were unprecedented both in the history of the People's Republic and the history of Beijing, a city with a tradition of popular protests against ruling authorities dating back to the May Fourth Movement of 1919. The subject of the Tiananmen protests in general and the military's role in the crackdown remains forbidden from public discussion in China.[4] The killings in Beijing continue to taint the legacies of the party elders, led by Deng Xiaoping, and weigh on the generation of leaders whose careers advanced as their more moderate colleagues were purged or sidelined at the time.[4] Within China, the role of the military in 1989 remains a subject of private discussion within the ranks of the party leadership and PLA.[4] Only outside of China is the subject part of the public discourse.

doc9

The protests were triggered in April 1989 by the death of former Communist Party General Secretary Hu Yaobang, a liberal reformer who was deposed after losing a power struggle with hardliners over the direction of political and economic reforms.[8] University students marched and gathered in Tiananmen Square to mourn. Hu had also voiced grievances against inflation, limited career prospects, and corruption of the party elite.[9] The protesters called for government accountability, freedom of the press, freedom of speech, and the restoration of workers' control over industry.[10][11] At the height of the protests, about a million people assembled in the Square.[12] Most of them were university students in Beijing.

