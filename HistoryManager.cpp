
#include "HistoryManager.h" 
#include "DisplayHandler.h" 
#include <unistd.h>
/*
Log 
date : 2/11/24
@author maria colon 
worked with theint to impliment the save(), adddirectory(), removeduplicate(),clear()and setdirectory(). 
toDO gethistory ().

date 2/18/24 
@author maria colon 
finaly implemeted get history 
date 2/22/24
@author 
summary of the past few days:
*/

 /**
     * @name HistoryManeger
     * @def  writes list of directories to the directory log file. 
    */
        HistoryManager::HistoryManager()
        {
            std::string log; 
            std::ifstream logFile(baseDir + "/Directories.log"); //Edited (JM)
            while(std::getline(logFile,log)){
                directory.push_back(log);
            }
            logFile.close();
        }
        HistoryManager::~HistoryManager(){} 
         /**
         * @name getHistory
         * @def Gets the full list of directories this program has handled when
         * the user changed directories. This does not include the user changing
         * the directory outside of the use of this program.
        */
       /*return list of all strings  */
      std::list<std::string>  HistoryManager::getHistory(){
        return getHistory(1);
      }

       
       /**
         * @name getHistory
         * @def Gets a list of the directories the user has changed to, but limits
         * the display of the directories based on where to beginning display. (ie.
         * only show the directories start at and after the given value).
         * @param startPoint INT - Starting point in the history list
        */
       /* return list of strings form stating point to end */
        std::list<std::string> HistoryManager::getHistory(int startPoint){
            std::list<std::string>history;
            for(int i=startPoint - 1; i < directory.size(); i++ ){
                history.push_back(directory.at(i));
            }
            return history;
         }
         /**
         * @name setDirectory
         * @def Sets the directory at the given line number. This will overwrite the
         * directory at the given line number.
         * @param lineNumber int - Line number to set the directory at
         * 
         * for (auto it = myList.begin(); it != myList.end(); ++it) {
        if (count == index) {
            std::cout << "Element at index " << index << ": " << *it << std::endl;
            break; // Stop the loop once the desired index is found
        }
        ++count;
    }
        */
        void HistoryManager::setDirectory(int lineNumber){
           if(lineNumber<=directory.size()&&lineNumber>0){
                const char* temp = directory.at(lineNumber-1).c_str();
                chdir(temp);
                addDirectory(directory.at(lineNumber - 1));     // Edit (JM)
                save();
           }
            
            
        }
         /**
         * @name clear
         * @def Clears the history log, removing all stored directories.
        */
        void HistoryManager::clear(){
            directory.clear();
            save(); // Edit (JM)
        }
         /**
         * @name removeDuplicates
         * @def Removes any duplicate directories found within the log. The NEWEST
         * found directory is kept while all older directories are removed.
        */
        void HistoryManager::removeDuplicates(){
            std::vector<std::string> temp;
            for (int i=0; i<directory.size();i++){
                temp.push_back(directory.at(i));
            }
            std::sort( temp.begin(),temp.end());
            auto it = std::unique(temp.begin(),temp.end());
            temp.erase(it,temp.end());
            directory.clear();
            
            for(int i = 0; i < temp.size(); i++)
                directory.push_back(temp.at(i));

            save(); // Edited (JM)
        }
         /**
         * @name addDirectory
         * @def Adds a directory to the log at the end (last). This does not care whether
         * the directory already exists within the log.
         * @param dir STRING - Directory to add to log
        */
        void HistoryManager::addDirectory(std::string dir){ 
            directory.push_back(dir);
            save(); // Edit (JM)
        }
         /**
         * @name save
         * @def This method is called when the data needs to be saved to the log file.
        */
         void HistoryManager::save(){
            std::ofstream logFile(baseDir.substr(1) + "/Directories.log");
            logFile.open (baseDir + "/Directories.log");

            std::string log = "";
            for(int i=0;i < directory.size();i++){
                log += directory.at(i) + "\n";
            }//end for
            logFile << log;
            logFile.close(); // Edit (JM)
        }
            