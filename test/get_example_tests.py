from sys import argv

import requests
from lxml import html, etree

problem_page_url = argv[1]

print "Downloading problem page..."

page = requests.get(problem_page_url).content

doc = html.document_fromstring(page)

input_divs = doc.cssselect('div.sample-test div.input pre')
output_divs = doc.cssselect('div.sample-test div.output pre')

print "Found %d test case%s" % (len(input_divs), len(input_divs) != 1 and "s" or "" )

def pre_inner_html_to_text(s):
    return s.replace("<pre>", "").replace("</pre>", "").replace("<br/>", "\n")

for i in xrange(len(input_divs)):
    test_filename = "%02d.txt" % (i + 1, )

    with open(test_filename, mode='w') as f:


        f.write(pre_inner_html_to_text(etree.tostring(input_divs[i])))

        # TODO: also do something with expected outputs when run_tests.py supports it

    print "Saved %s" % (test_filename, )
