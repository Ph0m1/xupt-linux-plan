#include "smtpmailer.h"



SMTPMailer::SMTPMailer(const std::string& smtpServer, const std::string& username, const std::string& password) : smtpServer(smtpServer), username(username), password(password) {
    curl_global_init(CURL_GLOBAL_DEFAULT); // 全局初始化libcurl
    curl = curl_easy_init(); // 初始化一个curl会话
}

SMTPMailer::~SMTPMailer() {
    if (curl) {
        curl_easy_cleanup(curl); // 清理curl会话
    }
    curl_global_cleanup(); // 清理全局libcurl资源
}

bool SMTPMailer::sendMail(const std::string& from, const std::vector<std::string>& to,
              const std::string& subject, const std::string& body) {
    if (!curl) {
        return false;
    }

    struct curl_slist *recipients = NULL; // 收件人列表
    struct upload_status uploadCtx = { 0 }; // 邮件上传状态

    // 添加收件人到收件人列表
    for (const auto& recipient : to) {
        recipients = curl_slist_append(recipients, recipient.c_str());
    }

    // 生成邮件内容的payload
    std::vector<std::string> payloadText = generatePayload(from, to, subject, body);
    uploadCtx.payloadText = &payloadText;

    // 设置curl选项
    curl_easy_setopt(curl, CURLOPT_USERNAME, username.c_str()); // 设置用户名
    curl_easy_setopt(curl, CURLOPT_PASSWORD, password.c_str()); // 设置密码
    curl_easy_setopt(curl, CURLOPT_URL, smtpServer.c_str()); // 设置SMTP服务器地址
    curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL); // 启用SSL/TLS
    curl_easy_setopt(curl, CURLOPT_MAIL_FROM, from.c_str()); // 设置发件人地址
    curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients); // 设置收件人地址
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, payloadSource); // 设置读取数据的回调函数
    curl_easy_setopt(curl, CURLOPT_READDATA, &uploadCtx); // 设置读取数据的上下文
    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L); // 启用上传

    // 执行邮件发送
    CURLcode res = curl_easy_perform(curl);
    curl_slist_free_all(recipients); // 释放收件人列表

    if (res != CURLE_OK) {
        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        return false;
    }

    return true;
}


size_t SMTPMailer::payloadSource(void* ptr, size_t size, size_t nmemb, void* userp) {
    struct upload_status* uploadCtx = static_cast<struct upload_status*>(userp);
    const std::vector<std::string>& payloadText = *uploadCtx->payloadText;

    if ((size == 0) || (nmemb == 0) || ((size * nmemb) < 1)) {
        return 0;
    }

    if (uploadCtx->linesRead < payloadText.size()) {
        const std::string& data = payloadText[uploadCtx->linesRead];
        size_t len = data.size();
        memcpy(ptr, data.c_str(), len); // 复制数据到ptr
        uploadCtx->linesRead++;
        return len;
    }

    return 0;
}

std::vector<std::string> SMTPMailer::generatePayload(const std::string& from, const std::vector<std::string>& to,
                                         const std::string& subject, const std::string& body) {
    std::vector<std::string> payload;
    payload.push_back("To: " + join(to, ", ") + "\r\n");
    payload.push_back("From: " + from + "\r\n");
    payload.push_back("Subject: " + subject + "\r\n");
    payload.push_back("\r\n"); // 邮件头和正文的分隔符
    payload.push_back(body + "\r\n");
    return payload;
}

std::string SMTPMailer::join(const std::vector<std::string>& list, const std::string& delimiter) {
    std::string result;
    for (size_t i = 0; i < list.size(); ++i) {
        result += list[i];
        if (i < list.size() - 1) {
            result += delimiter;
        }
    }
    return result;
}

std::string SMTPMailer::getcode(){
    std::srand(static_cast<unsigned int>(std::time(0)));
    std::ostringstream idStream;
    for (int i = 1; i < 6; ++i) {
        int digit = rand() % 10; // 生成0到9之间的随机数
        idStream << digit;
    }
    return idStream.str();
}
