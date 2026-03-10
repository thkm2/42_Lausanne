#include "../incl/lib.hpp"

std::string itos(int value) {
        std::stringstream ss;
        ss << value;
        return ss.str();
}

std::string extractQuotedValue(const std::string s)
{
    size_t start = s.find('"');
    size_t end = s.rfind('"');
    if (start != std::string::npos && end != std::string::npos && end > start)
        return s.substr(start + 1, end - start - 1);
    return "";
}

std::string getDefaultErrorPage(int code, const std::string &message)
{
    std::string body = "<!doctype html>\n"
        "<html lang=\"fr\">\n"
        "<head>\n"
        "<meta charset=\"UTF-8\" />\n"
        "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\" />\n"
        "<title>Error - Webserv</title>\n"
        "<script src=\"https://cdn.jsdelivr.net/npm/@tailwindcss/browser@4\"></script>\n"
        "</head>\n"
        "<body class=\"min-h-screen bg-zinc-950 text-zinc-50 flex items-center justify-center p-4\">\n"
        "    <div class=\"w-full max-w-2xl\">\n"
        "        <div class=\"relative rounded-xl border border-zinc-800 bg-zinc-900/50 shadow-2xl\">\n"
        "            <div class=\"absolute rounded-xl inset-0 bg-gradient-to-br from-zinc-900 via-zinc-900 to-zinc-950 opacity-80\"></div>\n"
        "            \n"
        "            <div class=\"relative p-12\">\n"
        "                <div class=\"flex items-center gap-3 mb-6\">\n"
        "                    <div class=\"flex h-12 w-12 items-center justify-center rounded-lg bg-red-500/10 ring-1 ring-red-500/20\">\n"
        "                        <svg class=\"h-6 w-6 text-red-500\" fill=\"none\" stroke=\"currentColor\" viewBox=\"0 0 24 24\">\n"
        "                            <path stroke-linecap=\"round\" stroke-linejoin=\"round\" stroke-width=\"2\" d=\"M12 9v2m0 4h.01m-6.938 4h13.856c1.54 0 2.502-1.667 1.732-3L13.732 4c-.77-1.333-2.694-1.333-3.464 0L3.34 16c-.77 1.333.192 3 1.732 3z\" />\n"
        "                        </svg>\n"
        "                    </div>\n"
        "                    <div>\n"
        "                        <div class=\"h-12 flex items-center justify-center rounded-md border border-zinc-700 bg-zinc-800/50 px-4\">\n"
        "                            <span class=\"text-lg font-medium text-zinc-400\">Error</span>\n"
        "                            <span class=\"ml-2 text-lg font-bold text-zinc-100\" id=\"errorCode\">" + itos(code) + "</span>\n"
        "                        </div>\n"
        "                    </div>\n"
        "                </div>\n"
        "\n"
        "                <h1 class=\"text-5xl font-bold tracking-tight mb-4 bg-gradient-to-br from-zinc-100 to-zinc-400 bg-clip-text text-transparent\">\n"
        "                    " + message + "\n"
        "                </h1>\n"
        "                \n"
        "                <div>\n"
        "                    <p class=\"text-lg text-zinc-400 leading-relaxed\">\n"
        "                        #miskine #groslooser #lahonte\n"
        "                    </p>\n"
        "                    <a href=\"https://youtu.be/hYfz5adLxJc\" class=\"text-lg text-zinc-400 leading-relaxed hover:text-zinc-300 hover:underline duration-150\">\n"
        "                        #bahcestbiennilssuperpourlappareilphoto\n"
        "                    </a>\n"
        "                </div>\n"
        "            </div>\n"
        "\n"
        "        </div>\n"
        "    </div>\n"
        "</body>\n"
        "</html>\n";
    return body;
}