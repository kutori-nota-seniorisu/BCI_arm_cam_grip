#### 1、初始化本地仓库
进入功能包（仓库）后，执行 git init，将当前功能包初始化为本地仓库
#### 2、将远程仓库与本地仓库连接
执行git remote add origin git@github.com:Edify0991/Teleoperation_visual.git，将远程仓库与本地仓库连接
#### 3、拉取远程仓库信息
执行git pull，拉取远程仓库信息
#### 4、查看分支
执行git branch -a，可查看本地及远程仓库现有的分支
#### 5、新建分支
执行git branch Edify_Cd，新建一个本地分支，用来和远程仓库的分支连接
如果在这一步报错**fatal: 不是一个有效的对象名：'master'**，则需要先在本地仓库进行一次提交，否则无法获取本地仓库的分支master
执行git add 文件名
执行git commit -m "first commit"，进行提交
此时再执行git branch -a，即可显示master分支
#### 6、切换分支
后面的操作需要连接本地仓库与远程仓库对应的分支，所以先切换到我们的目标分支
执行git checkout Edify_Cd 
#### 7、本地该分支连接到远程仓库对应分支
执行git branch -u origin/Edify_Cd，可将本地该分支连接到远程仓库对应分支
#### 8、Commit&Push
这时可以在vscode左侧工具栏找到Source Control，在命令行中输入commit的说明后，点击commit&Push
如果这时候报错显示**fatal: 拒绝合并无关的历史**
则执行git pull origin Edify_Cd  --allow-unrelated-histories，强制将代码合并到git仓库中
### 至此，将新建的功能包（本地仓库）上传并链接到远程仓库的过程就完毕了！
#### 更新gitignore文件后不生效
在更新gitignore文件后直接提交是没有办法生效的，需要执行git rm -r --cached 路径/文件名来先删除仓库的记录，想让哪个生效，删哪个缓存就好，之后在.gitignore配置即可生效
