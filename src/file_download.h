#ifndef FILEDOWNLOAD_H
#define FILEDOWNLOAD_H


#include <curl/curl.h>

#include "string_utils.h"
#include "file_utils.h"

class FileDownload
{
	public:

	FileDownload(std::string url, std::string dirName, std::string fileName, bool progress);
	FileDownload(std::string url, std::string dirName, std::string fileName, std::string MD5Sum , bool progress);
	FileDownload(std::vector<InfoFile> destinationFiles,bool progress);
	~FileDownload()
	{
		curl_slist_free_all(m_slist);
		curl_global_cleanup();
		curl_easy_cleanup(m_curl);
	}
	bool checkMD5sum();
	void downloadFile();

	private:
	static int updateProgressHandle(void *p, double dltotal, double dlnow, double ultotal, double ulnow);
	static size_t writeToStreamHandle(void *buffer, size_t size, size_t nmemb, void *stream);
	int updateProgress(void *p, double dltotal, double dlnow, double ultotal, double ulnow);
	size_t writeToStream(void *buffer, size_t size, size_t nmemb, void *stream);
	void initFileToDownload(std::string _url, std::string _file);
	bool checkUpToDate();
	struct dwlProgress
	{
		double lastruntime;
		CURL *curl;
	};
	struct curl_slist *m_slist;
	void updateProgress();

	CURL*       m_curl;
	CURLcode    m_curlCode;
	dwlProgress m_downloadProgress;
	InfoFile    m_destinationFile;
	string      m_url;
	string      m_downloadFileName;
	bool        m_checkMD5;
	bool        m_progress;
	string      m_MD5Sum;
};

#endif /* FILEDOWNLOAD_H */
// vim:set ts=2 :
