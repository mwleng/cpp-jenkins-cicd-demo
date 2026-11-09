pipeline {
    agent none
    options {
        timestamps()
        skipDefaultCheckout(true)
    }
    stages {
        stage('Build and test') {
            matrix {
                axes {
                    axis {
                        name 'COMPILER'
                        values 'gcc', 'clang'
                    }
                }
                agent { label 'ubuntu' }
                stages {
                    stage('Checkout') {
                        steps { checkout scm }
                    }
                    stage('Configure') {
                        steps { sh "./scripts/configure.sh build-${COMPILER} ${COMPILER}" }
                    }
                    stage('Compile') {
                        steps { sh "cmake --build build-${COMPILER} --parallel" }
                    }
                    stage('Test') {
                        steps { sh "ctest --test-dir build-${COMPILER} --output-on-failure" }
                    }
                }
            }
        }
        stage('Package') {
            agent { label 'ubuntu' }
            steps {
                checkout scm
                sh './scripts/package.sh'
                archiveArtifacts artifacts: 'dist/*', fingerprint: true
            }
        }
        stage('Publish GitHub release') {
            when {
                branch 'main'
            }
            steps {
                withCredentials([
                    string(
                        credentialsId: 'github-release-token-secret',
                        variable: 'GH_TOKEN'
                    )
                ]) {
                    sh '''
                        set -eu
                        gh release create "$TAG_NAME" dist/* \
                            --repo mwleng/cpp-jenkins-cicd-demo \
                            --verify-tag \
                            --generate-notes
                    '''
                }
            }
        }        
    }
}

