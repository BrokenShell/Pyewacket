from setuptools import setup, Extension
from Cython.Build import cythonize


with open("README.md", "r") as file:
    long_description = file.read()

setup(
    name="Pyewacket",
    ext_modules=cythonize(
        Extension(
            name="Pyewacket",
            sources=["Pyewacket.pyx"],
            language=["c++"],
            extra_compile_args=["-std=gnu++17"],
        ),
        compiler_directives={
            'embedsignature': True,
            'language_level': 3,
        },
    ),
    author="Robert Sharp",
    author_email="webmaster@sharpdesigndigital.com",
    requires=["Cython"],
    version="1.3.8",
    description="Drop-in Replacement for the Python Random Module.",
    long_description=long_description,
    long_description_content_type="text/markdown",
    license="Free for non-commercial use",
    platforms=["Darwin", "Linux"],
    classifiers=[
        "Development Status :: 5 - Production/Stable",
        "Programming Language :: Python :: 3.6",
        "Programming Language :: Cython",
        "Programming Language :: C++",
        "Operating System :: MacOS :: MacOS X",
        "Operating System :: POSIX :: Linux",
        "Topic :: Software Development :: Libraries :: Python Modules",
    ],
    keywords=[
        "Pyewacket", "random module replacement",
    ],
    python_requires='>=3.6',
)
