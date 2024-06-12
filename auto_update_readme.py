#!/usr/bin/env python

import os
import re
from urllib.parse import quote


PS_SITES = ["백준", "프로그래머스"]
TIERS = ("Ruby", "Diamond", "Platinum", "Gold", "Silver", "Bronze", "Unrated")
PROBLEM_PATTERN = re.compile(r"(?P<ID>\d+)[.]\s*(?P<NAME>.*)\s*")


def main():
    readme_lines = [f"# {' / '.join(PS_SITES)} 문제 풀이 목록"]

    for ps_site in PS_SITES:
        directory = f"./{ps_site}"
        if not os.path.exists(directory):
            continue

        readme_lines.append(f"## 📚 {ps_site}")
        for tier in TIERS:
            tier_directory = os.path.join(directory, tier)
            if not os.path.exists(tier_directory):
                continue

            problems = sorted(os.listdir(tier_directory), key=lambda p: int(PROBLEM_PATTERN.match(p)['ID']))

            readme_lines.append(f"### 🚀 {tier} <{len(problems)} 문제 해결>")
            readme_lines.append("| 번호 | 문제 |")
            readme_lines.append("| ----- | ----- |")

            for problem in problems:
                m = PROBLEM_PATTERN.match(problem)
                readme_lines.append(f"| {m['ID']}"
                                    f" | [{m['NAME']}]({quote(os.path.join(tier_directory,problem, 'README.md'))}) |")

    with open("./README.md", "w", encoding="utf-8") as f:
        f.write("\n".join(readme_lines))


if __name__ == "__main__":
    main()
