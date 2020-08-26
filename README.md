# SimpleRA

## Compilation Instructions

We use ```make``` to compile all the files and creste the server executable. ```make``` is used primarily in Linux systems, so those of you who want to use Windows will probably have to look up alternatives (I hear there are ways to install ```make``` on Windows). To compile

```cd``` into the SimpleRA directory
```
cd SimpleRA
```
```cd``` into the soure directory (called ```src```)
```
cd src
```
To compile
```
make clean
make
```

## To run

Post compilation, an executable names ```server``` will be created in the ```src``` directory
```
./server
```
## To setup your Git Repository
- Join the course github organisation using the invite link.
- Join or create a team corresponding to your team name on the organisation.
- Your repository will be initialised with a template code on succesful authorisation.
- Now clone your personal repo using ```git clone "your repo link"```.
- After you have cloned your repo to your system add the main repo as an upstream to your repo so whenever a change is pushed by TA's you can access it.
- To set it as upstream type ```git remote add upstream https://github.com/SimpleRA/SimpleRA.git```.
- Now it will be added as upstream.
- To fetch the changes made by TA's just type ```git pull upstream master --allow-unrelated-histories``` .
- Manually merge conflicts if there are any !!


## Git tutorials
- [Basic github tutorial](https://youtu.be/SWYqp7iY_Tc)
- [Handling git merge conflicts](https://youtu.be/JtIX3HJKwfo)
- [What is git stash?](https://youtu.be/KLEDKgMmbBI)
- [The best way is documentation itself](https://docs.github.com/en)

## Instructions for Creating a Pull Request
- First fork the repo from the main code repository.
- Then commit your changes to this forked repository.
- To create a pull request go to the main repository and click on the pull request option.
- Kindly only submit your pull requests to the branch **student-pull-requests** only. We won't entertain pull requests to master branch.
