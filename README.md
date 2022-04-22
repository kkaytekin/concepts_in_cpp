# CIIP C++ Course

Welcome to the CIIP course **Concepts of C++ programming**!

You will use this [`git`](https://git-scm.org) repository for solving and submitting homeworks.


## Overview


Your personal "fork" of the [base repo](https://gitlab.lrz.de/cppcourse/ss2022/tasks) (`your-username_tasks`) contains all the code.

You will [pull](https://git-scm.com/docs/git-pull) new assignments from the base repo (`upstream`) and [push](https://git-scm.com/docs/git-push) your changes to your repo (`origin`) to submit.
In other words, you "download" the new assignment from the base repo to your computer and then "upload" your solution to your GitLab repo.

**Getting and Submitting new Homeworks**
We will publish new homeworks (and bugfixes :) [**in the base repo**](https://gitlab.lrz.de/cppcourse/ss2022/tasks), which you then merge into [**your repo**](https://gitlab.lrz.de/cppcourse/ss2022) (`your-username_tasks`).
If everything is setup correctly it is as simple as (*pseudo code!*):

``` console
$ git pull upstream  # get the new homework
# do the homework
$ git add .  # add the changes you want to commit
$ git commit -m "submission"  # create the commit
$ git push origin  # push the changes to your Gitlab repository
```
Pushing the changes will trigger the build server, compile your code and run the unit tests ([CI](https://en.wikipedia.org/wiki/Continuous_integration#Workflows)). At the end of each assignment period we will collect the submissions, test them and notify you in an [issue](https://docs.gitlab.com/ee/user/project/issues/) if your submission passed or not.


## Setup

This section explains how you set everything up on your machine.
If you have any questions, post it on [Zulip](https://zulip.in.tum.de/) so that we can help you and other students can refer to it.

**Table of Contents**

[[_TOC_]]


### SSH-Key

Instead of always typing your username and password when communicating with Gitlab using git we recommend to set up an SSH key.

1. [Generate an SSH key pair](https://docs.gitlab.com/ee/user/ssh.html#generate-an-ssh-key-pair)
2. [Add an SSH key to your GitLab account](https://docs.gitlab.com/ee/user/ssh.html#add-an-ssh-key-to-your-gitlab-account)
3. Add the new key to you SSH config
    In your home folder (`~/` on Mac/Linux and `C:\Users\You` on Windows) you should now see the `.ssh` (hidden) folder, containing the new SSH-Key (provided you saved the file in the default directory). If not present, create a new file named `config` (without any suffix) and add the following:

    ```
Host gitlab.lrz.de
  Preferredauthentications publickey
  IdentityFile ~/.ssh/#your-private-key-file#
   ```

   This tells the SSH-Agent to use this private key for the gitlab.lrz.de server.


### Git

You'll need git in order to interact with your repository. [This tutorial](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git), 
will show you the installation process for most operating systems.


### Downloading your Repository (Clone)
- On Gitlab you get your remote link by clicking on `Clone` on the main page of your repository.
- Choose the link under *Clone with SSH*.
- Navigate to the directory where you want to download your project and use `git clone <your-link`, i.e
use `git clone git@gitlab.lrz.de:cppcourse/${cfg.term}/your-username_tasks.git` (or `git clone https://gitlab.lrz.de/cppcourse/${cfg.term}/your-username_tasks.git` if you're using HTTPS).

<%text>
### Add the base task repo (upstream) to get the 


In order to regularly pull the new assignments and any other changes (bugfixes), you must add the original [base repo](https://gitlab.lrz.de/cppcourse/ss2022/tasks) as `upstream` remote. 

To do this, navigate to your cloned project's directory and use the following commands from the console:

First check the original setup with:
```console
$ git remote -v
```

The output should be:
```console
> origin  git@gitlab.lrz.de:cppcourse/ss2022/your-username_tasks.git (fetch)
> origin  git@gitlab.lrz.de:cppcourse/ss2022/your-username_tasks.git (push)
```
which tells us, that remote with the name origin (your Gitlab repo) points to your local repo. To add the [base repo](https://gitlab.lrz.de/cppcourse/ss2022/tasks) use:
```console
$ git remote add upstream git@gitlab.lrz.de:cppcourse/ss2022/tasks.git
```
This command adds a the base repo as `upstream`.
Again, you can verify that it was added:
```console
$ git remote -v
> origin  git@gitlab.lrz.de:cppcourse/ss2022/your-username_tasks.git (fetch)
> origin  git@gitlab.lrz.de:cppcourse/ss2022/your-username_tasks.git (push)
> upstream  git@gitlab.lrz.de:cppcourse/ss2022/tasks.git (fetch)
> upstream  git@gitlab.lrz.de:cppcourse/ss2022/tasks.git (push)
```
If there are changes / new assignments you can pull them with `git pull upstream`.


### Get the new assignment


If you want to get the new assignments or other changes, go to your project directory and use:
```console
$ git pull upstream master
$ git checkout master
$ git merge upstream/master
```

This first pulls the information from the base project, where we publish the homeworks to, and into `upstream/master`
Then, it switches (`checkout`) to the `master` branch (if you know you're on the master branch, you can omit this step).
Finally, it merges the current master with `upstream/master`.
For new assignments, we always use new files, so this should work without any merge conflicts.

However, if both of us changed the same file, a merge conflict might happen if the changes aren't compatible, in which case you need to resolve the conflict before you can start working.


### Build system (CMake)

We use the [CMake](https://cmake.org/) build system.
It takes care of building/compiling everything in the right order and hooking everything up, rather than forcing us to manually manage (and possibly forget) some elements or links.
Follow [this tutorial](https://cmake.org/install/) to install CMake.


### Compiler


As we'll be covering modern C++ (C++20) you need a recent compiler, otherwhise your project will not compile.
Possible compilers are
- GCC 10 and higher
- Clang 10 and higher
- Visual Studio 2019 16.10.0 and higher

We will be testing with GCC and Clang on Linux.
It therefore could be possible that you encounter errors with other versions.

### IDE

You can use any text editor you are comfortable with (we use Emacs).
We recommend [CLion](https://www.jetbrains.com/community/education/#students) or [VSCode](https://code.visualstudio.com/) if you don't have any preference, yet.



