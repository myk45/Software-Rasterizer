#ifndef FILE_IO
#define FILE_IO

#include "CommonIncludes.h"
#include "VertexAttribBuffer.h"

/** 
 * @ Class FileIO. This handles all the IO operations w.r.t files. i.e File opening, closing. This can be a singleton.
 * @ So, this class is something like a FileIO manager.
 */


class FileIO {
	protected:
		  static FileIO* m_psFileIO;	 // Singleton instance of the FileIO manager! 
		  FileIO();					     // Protected constructor, restricting the creation of only one FileIO instance.
		  std::map<std::string, FILE*> mMFileMap;

	public:
		   //static void vCreateInstance();  // Creates the singleton instance of the class.
		   static FileIO* vGetInstance();     // Returns the singleton. [create it as inline?]		   

		   FILE* fpFileOpen(std::string fileName, std::string mode); // Opens a file. returns a NULL if file was not opening properly.
		   bool bClose(const std::string& fileName);	

		   int iReadFileAndFillAttribs(VertexAttribBuffer* vertAttrib, std::string fileName);
		   int iReadBytes(unsigned char *dest, int num, FILE *fp);
		   int iReadLine(char *buff, std::string fileName);  
};

#endif