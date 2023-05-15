from dis import dis
from lib import *

module_function()


class Doc:
    def greet(self):
        print('Hello World!')


doc = Doc()

doc.greet()

print(type(Doc))
print(id(Doc))
print(type(doc))
print(id(doc))

cp = doc
print(id(cp))

assert isinstance(doc, Doc)
assert hasattr(doc, 'greet')

print(doc.__class__)
print(doc.__class__.__name__)
print(doc.__class__.__bases__)
print(doc.greet.__name__)


print(dis(Doc))
print(dis(doc.greet))
