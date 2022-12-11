#ifndef TRIVIADOR_QUESTIONCHOICE_H
#define TRIVIADOR_QUESTIONCHOICE_H

namespace Server {
    template<typename T>
    class QuestionChoice {
    public:
        // constructors
        QuestionChoice(T choice, bool isCorrect);
        QuestionChoice(const QuestionChoice& other) = default;
        QuestionChoice& operator=(const QuestionChoice& other) = default;

        ~QuestionChoice() = default;

        // getters
        T GetChoice() const;
        bool GetIsCorrect() const;

        // setters
        void SetChoice(T choice);
        void SetIsCorrect(bool isCorrect);
    private:
        T m_choice;
        bool m_isCorrect;
    };

    template<typename T>
    QuestionChoice<T>::QuestionChoice(T choice, bool isCorrect)
        :
         m_choice(choice)
        ,m_isCorrect(isCorrect)
    {}

    template<typename T>
    T QuestionChoice<T>::GetChoice() const {
        return m_choice;
    }

    template<typename T>
    bool QuestionChoice<T>::GetIsCorrect() const {
        return m_isCorrect;
    }

    template<typename T>
    void QuestionChoice<T>::SetChoice(T choice) {
        m_choice = choice;
    }

    template<typename T>
    void QuestionChoice<T>::SetIsCorrect(bool isCorrect) {
        m_isCorrect = isCorrect;
    }
}


#endif //TRIVIADOR_QUESTIONCHOICE_H
