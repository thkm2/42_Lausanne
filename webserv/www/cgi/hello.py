#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import os
import sys
from urllib.parse import parse_qs

method = os.environ.get('REQUEST_METHOD', 'GET')
name = "l'ami"

if method == 'GET':
    query_string = os.environ.get('QUERY_STRING', '')
    if query_string:
        params = parse_qs(query_string)
        name = params.get('name', ["l'ami"])[0]

elif method == 'POST':
    content_length = int(os.environ.get('CONTENT_LENGTH', 0))
    if content_length > 0:
        post_data = sys.stdin.read(content_length)
        params = parse_qs(post_data)
        name = params.get('name', ["l'ami"])[0]

print("Content-Type: text/html; charset=utf-8")
print()
print(f"""<!doctype html>
<html lang="fr">
<head>
<meta charset="UTF-8" />
<meta name="viewport" content="width=device-width, initial-scale=1.0" />
<title>CGI = Cheeseburger, Gros et Intelligent</title>
<script src="https://cdn.jsdelivr.net/npm/@tailwindcss/browser@4"></script>
</head>
<body class="min-h-screen bg-zinc-950 text-zinc-50 flex items-center justify-center p-4">
    <div class="w-full max-w-2xl">
        <div class="relative rounded-xl border border-zinc-800 bg-zinc-900/50 shadow-2xl">
            <div class="absolute rounded-xl inset-0 bg-gradient-to-br from-zinc-900 via-zinc-900 to-zinc-950 opacity-80"></div>
            
            <div class="relative p-12">
                <div class="flex items-center gap-3 mb-6">
                    <div class="flex h-12 w-12 items-center justify-center rounded-lg bg-green-500/10 ring-1 ring-green-500/20">
                        <svg class="h-6 w-6 text-green-500" fill="none" stroke="currentColor" viewBox="0 0 24 24">
                            <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M14.828 14.828a4 4 0 01-5.656 0M9 10h.01M15 10h.01M21 12a9 9 0 11-18 0 9 9 0 0118 0z" />
                        </svg>
                    </div>
                    <div>
                        <div class="h-12 flex items-center justify-center rounded-md border border-zinc-700 bg-zinc-800/50 px-4">
                            <span class="text-lg font-medium text-zinc-400">CGI</span>
                            <span class="ml-2 text-lg font-bold text-zinc-100">Python</span>
                        </div>
                    </div>
                </div>

                <h1 class="text-5xl font-bold tracking-tight mb-4 bg-gradient-to-br from-zinc-100 to-zinc-400 bg-clip-text text-transparent">
                    Adieu {name} ça joue&nbsp;?
                </h1>
                
                <div>
                    <p class="text-lg text-zinc-400 leading-relaxed mb-4">
                        Méthode utilisée : <span class="text-green-400 font-mono">{method}</span>
                    </p>
                    <p class="text-sm text-zinc-500">
                        Teste avec : <code class="bg-zinc-800 px-2 py-1 rounded">?name=Gérard</code>
                    </p>
                </div>
            </div>

        </div>
    </div>
</body>
</html>
""")