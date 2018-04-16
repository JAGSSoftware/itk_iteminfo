# Architecture and Design for Teamcenter ITK standalone tool

The project implements the functionality for `item_info` retrieving
some information about an item given its id:

* id
* name
* type
* number of revisions
* owning user (id and name)
* owning group name

The body of the ITK tool is in `standalone/item_info` folder. However it
is using the libraries in `lib`.

## Architecture

### Layers

The libraries have been split in *layers*:

* proxy: this is lowest layer using the Teamcenter API functions. The implementation
is done in `itkproxy`. At the time of this writing, it's using *Teamcenter 11* ITK
functions.
* connector: this layer connects the proxy and the business logic layer, not using
any Teamcenter API function but only some structures internally. Nothing related
to Teamcenter is public available from this layer. Its implementation is done in
`itkconnector`.

### Modules

The functionality in the libraries is not big enough to split it in modules, only
`itkproxy` has been split in three modules:

* `itkproxy`: generic functionality
* `itkproxy_item`: encapsulates functionality related to *Item*
* `itkproxy_pom`: encapsulates functionality related to *POM* objects

## Design and encapsulation
The code has been designed to encapsulate the functionality within the different modules,
not exposing any internal detail for public access unless using the *getters* or *setters*
function (in this project there aren't setters).

Therefore it can be found in a declaration file a structure declaration like:

```c
    typedef struct itk_Item itk_Item;
```

but its internal attributes are hidden. Beside this declaration, also the
declaration for the *getters*:

```c
    DLLEXPORT const char *itkc_item_getId(const itk_Item *item);
    DLLEXPORT const char *itkc_item_getName(const itk_Item *item);
    DLLEXPORT const char *itkc_item_getType(const itk_Item *item);
    DLLEXPORT int itkc_item_getNumRevisions(const itk_Item *item);
```

Because the `itk_Item` has been declared but not defined yet in the declaration file,
the functions having it as parameter must use a pointer to the structure instead of
the structure.

In the definition file can be found, however, the details of the structure:

```c
    typedef struct itk_Item
    {
        tag_t itk_ref;
        char *id;
        char *name;
        char *type;
        int numRevisions;
    } itk_Item;
```

Also bear in mind how the `itk_Item` was *constructed*. It is the return value of
the function:

```c
    DLLEXPORT itk_Item *itkc_findItem(const char *itemId)
```

## Support libraries

Not all libraries are functional split in layers. There are two libraries, `common`
and `util` that can used by any other library at any layer.

## Test
Beside the declaration and definition files there are xUnit implementation test
cases for the code. The framework used to implement the test cases is
[cmocka](https://cmocka.org).

It has been kept for reference.
